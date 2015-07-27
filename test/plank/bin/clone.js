#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , cp = require( 'child_process' )
  , fs = require( 'fs' )
  , emitter = new events.EventEmitter()
  , program = require( 'commander' )
  , join = require( 'path' ).join
  , config = require( './config' )
  , LIB_PATH = 'lib';

program
	.version( '0.0.0' )
	.option( '-p, --prefix [path]', 'output path' )
	.parse( process.argv )

installDependencies( config.readDependencies() );

function installDependencies( dependencies, index ) {
	
	if (typeof index === 'undefined')
		index = 0;

	if (index < dependencies.length)
	{

		fs.mkdirSync( LIB_PATH );

		var dependency = dependencies[ index ]
	      , name = config.libName( dependency )
	      , destination = config.getOutputDir(index)
	      , child = cp.spawn( 'git', [
	      		'-C',
				LIB_PATH,
				'clone',
				'--depth=1',
				dependency,
				name
			], {
				stdio: 'inherit'
			} );

		emitter.once( 'next dependency', function() {
			installDependencies( dependencies, index + 1 );
		} ); 

		child.on( 'exit', function( code ) {
			if (!code) {
				fs.appendFile( '.gitignore', LIB_PATH + '/\n', function(err){
					if (!err)
						console.log( 'repo cloned: ', name );
					else 
						console.log( 'error: sub repo ignore failed: ', err );
				});
			}
			else { 
				console.log( 'repo clone failed: ', name );
			}
			emitter.emit( 'next dependency', dependency, name );
		});
	}
}
	
