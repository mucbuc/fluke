var assert = require( 'assert' )
  , path = require( 'path' )
  , fs = require( 'fs' )
  , m_ = require( path.join( process.cwd(), 'm_.json' ) )

assert( typeof m_ !== 'undefined' ); 
assert( m_.hasOwnProperty( 'dependencies' ) );

var config = {
      readDependencies: function() {
          return m_.dependencies;
        },
      libName: function( dependency ) {
          return 'lib/' + path.basename( dependency, '.git' ); 
        }, 
      readOutputDir: function() {
          return m_.hasOwnProperty('outputDir') ? m_.outputDir : '';
        },
      getOutputDir: function(index) {
          var name = config.libName( m_.dependencies[index] );
          return path.join( config.readOutputDir(), name );
        },
      isCloned: function() {
          var p = '.gitignore';
          if (fs.existsSync(p)) {
            var ignore = fs.readFileSync( '.gitignore' );
            return ignore.toString().match( 'lib/' ) ? true : false;
          }
          return false;
        }
    };

module.exports = config;
