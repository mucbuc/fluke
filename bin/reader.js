var assert = require( 'assert' )
  , path = require( 'path' )
  , m_ = require( path.join( process.cwd(), 'm_.json' ) );

assert( m_.hasOwnProperty( 'dependencies' ) );

function readDependencies() {
	return m_.dependencies;
}

function libName( dependency ) {
	return 'lib/' + path.basename( dependency, '.git' ); 
}

function readOutputDir() {
	return m_.hasOwnProperty('outputDir') ? m_.outputDir : '';
}

module.exports.readDependencies = readDependencies;
module.exports.libName = libName;
module.exports.readOutputDir = readOutputDir;
