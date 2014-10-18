#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , util = require( 'util' )
  , ansi = require( 'ansi' )
  , cursor = ansi( process.stdout )
  , program = require( 'commander' );

assert( typeof cp !== 'undefined' );

program
	.version( '0.0.0' )
	.option( '-p, --path [path]', 'test path' )
	.parse( process.argv );

if (!program.path) {
	program.path = path.join( __dirname, '../../test/def/' );
}

attachLogic( emitter );

emitter.emit( 'traverse', program.path );

function attachLogic(emitter) {

	emitter.on( 'run', function( defFile, testDir, targetName ) {
		begin( defFile, 'run' );
		run( defFile, testDir, targetName, function(exitCode) {
			if (!exitCode) {
				finishGreen( defFile );
				console.log( '=> ' + targetName + ' passed' );
			}
			else {
				finishRed( defFile ) ; 
				console.log( '=> ' + targetName + ' failed with exit code:', exitCode );
			}
		});
	}); 

	emitter.on( 'build', function( defFile, testDir ) {
		begin( defFile, 'build' );
		build( defFile, testDir, function( exitCode, targetName, buildDir ) { 
			if (!exitCode) {
				finishGreen( defFile );
				emitter.emit( 'run', defFile, buildDir, targetName );
			}
			else {
				finishRed( defFile );
			}
		});
	});

	emitter.on( 'generate', function( defFile, testDir ) {
		begin( defFile, 'generate' );
		generate( defFile, testDir, function( exitCode, buildDir ){
			finishGreen( defFile, 'generate' );
			if (!exitCode) {
				emitter.emit( 'build', defFile, buildDir );
			}
		});
	});

	emitter.on( 'traverse', function(testDir) {
		
		fs.exists(testDir, function(exists) {
			if (exists) { 
					traverse( testDir, function(gypFile) {
						emitter.emit( 'generate', gypFile, testDir );
					});
			}
			else {
				cursor.red();
				process.stdout.write( 'invalid test definition path: ');
				cursor.reset();
				console.log( testDir ); 
			}
		});


	});

	function begin( msg1, msg2 ) {
		cursor.green();
		process.stdout.write( msg1 + ': ' );
		cursor.reset();
		console.log( msg2 );
		console.time( msg1 );
	}

	function finishGreen( msg1 ) {
		cursor.green();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function finishRed( msg1 ) {
		cursor.red();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function traverse( testDir, cb ) {
		fs.readdir( testDir, function( err, files ) {
				files.forEach( function( file ) {
					if (path.extname(file) == '.gyp') {
						cb( file ); 
					}
				} );	
			} );
	}

	function generate( defFile, testDir, cb ) {
		var cwd = path.join( testDir, '../build' );
		makePathIfNone(cwd, function() {
			var linkSrc = path.join( testDir, defFile )
			  , linkDst = path.join( cwd, defFile );
			
			fs.symlink( linkSrc, linkDst, function() {
				cp.spawn( 
					'gyp', 
					[
						linkDst,
						'--depth==0'
					], {
						cwd: cwd, 
						stdio: 'inherit'
					})
				.on( 'close', function( code ) {
					cb( code, cwd );
					fs.unlink( linkDst ); 
				});
			});
		});

		function makePathIfNone( path, cb ) {
			fs.exists(path, function(exists) {
				if (exists) 
					cb();
				else 
					fs.mkdir( path, [], cb ); 
			});
		}
	}

	function build( defFile, buildDir, cb ) {
		readTargetName( defFile, buildDir, function( targetName ) { 
			cp.spawn( 
				'xcodebuild', 
				[
					"-project",
					targetName + '.xcodeproj'
				], {
					cwd: buildDir
			} )
			.on( 'close', function( code ) {
				cb( code, targetName, buildDir ); 
			} );
		} );
	}

	function run( defFile, testDir, target, cb ) {
		cp.spawn( 
			path.join( testDir, 'build/Default', target ), 
			[], {
			stdio: 'pipe'
		})
		.on( 'close', function( code ) {
			cb( code );
		})
		.stdout.on( 'data', function( data ) {
			cursor.blue();
			process.stdout.write( defFile + ': ' ); 
			cursor.reset();
			console.log( data.toString() );
		});
	}

	function readTargetName(defFile, testDir, cb) {
		fs.readFile( path.join( testDir, defFile ), function( err, data ) {
			if (err) {
				cursor.red();
				process.stdout.write( defFile + ': ' );
				cursor.reset();
				console.log( err );
			}
			else {
				var matches = data.toString().match( /'target_name'\s*:\s*'(.*)'/ )
				if (matches) {
					cb( matches[1] );
				}
			}
		} ); 
	}
}
