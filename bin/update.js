#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , config = require( './config' );

function update( dependencies, index ) {
	if (typeof index === 'undefined') {
		index = 0;
	}
	if (index < dependencies.length) {
		var name = config.libName( dependencies[index] );
		console.log( 'pull ' + name );

		if (config.isCloned()) {
			cp.exec( 
				'git -C '
				+ config.getOutputDir(index)
				+ ' pull --squash origin master',
				finished ); 
		}
		else {
			cp.exec( 
				'git subtree pull -P ' 
				+ config.getOutputDir(index) 
				+ ' ' + name + ' master --squash',
				finished ); 
		}

		function finished(error, stdout, stderr) {
			if (error) 
			{
				console.log( error );
				throw error;
			}
			console.log( stdout );
			update( dependencies, index + 1 );
		}
	}
}

update( config.readDependencies() ); 
