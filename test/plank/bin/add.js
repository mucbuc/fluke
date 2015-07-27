#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , cp = require( 'child_process' )
  , emitter = new events.EventEmitter()
  , program = require( 'commander' )
  , path = require( 'path' )
  , remotes = ''
  , config = require( './config' );
  
program
	.version( '0.0.0' )
	.option( '-p, --prefix [path]', 'output path' )
	.parse( process.argv )

emitter.on( 'addSubtree', function( dependency, name ) {
	
	var child = cp.spawn( 'git', [
			'subtree',
			'add', 
			'-P',
			path.join( config.readOutputDir(), name ), 
			name,
			'master', 
			'--squash'
		], {
			stdio: 'inherit'
		});

	child.on( 'exit', function(code) {
		emitter.emit( 'next dependency');
	} );

});

emitter.on( 'readRemotes', function() {
	installDependencies( config.readDependencies() );
});

readRemotes(function(r) {
	remotes = r;
	emitter.emit( 'readRemotes' ); 
});

function readRemotes(cb) {

	var child = cp.spawn( 
			'git', 
			['remote', '-v'], 
			{ stdio: 'pipe' } 
		)
	  , remotes = '';
	
	child.stdout.on( 'data', function(data) {
		remotes += data;
	});

	child.on('exit', function() {
		cb( remotes.toString() );
	});
}

function installDependencies( dependencies, index ) {
	
	if (typeof index === 'undefined')
		index = 0;

	if (index < dependencies.length)
	{
		var dependency = dependencies[ index ]
	      , name = config.libName( dependency );

		if (remotes.match(dependency)) {
			emitter.emit( 'addSubtree', dependency, name );
		}
		else {
			var child
			  
			child = cp.spawn( 'git', [ 
					'remote',
					'add',
					'-f',
					name,
					dependency,
				], {
					stdio: 'inherit'
				} );

			emitter.once( 'next dependency', function() {
				installDependencies( dependencies, index + 1 );
			} ); 

			child.on( 'exit', function( code ) {
				if (!code) {
					console.log( 'remote added: ', name );
					emitter.emit( 'addSubtree', dependency, name );
				}
				else { 
					console.log( 'remote add failed: ', name );
					emitter.emit( 'addSubtree', dependency, name );
					//emitter.emit( 'next dependency');
				}
			});
		}
	} 
}
	
