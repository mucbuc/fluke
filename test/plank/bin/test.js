#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , program = require( 'commander' )
  , Base = require( './base' )
  , Logic = require( './logic' )
  , base
  , logic;

assert( typeof Logic !== 'undefined' );

program
  .version( '0.0.0' )
  .option( '-p, --path [path]', 'test path' )
  .option( '-o, --output [path]', 'build output' )
  .option( '-g, --gcc', 'use gcc compiler' )
  .parse( process.argv );

if (!program.path) {
  program.path = process.cwd();
}
else {
  program.path = path.join( process.cwd(), program.path );
}

if (!program.output) {
  program.output = path.join( process.cwd(), 'build' );
}
else {
  program.output = path.join( process.cwd(), program.output );
}

emitter.on( 'run', function( o ) {
  logic.run( o ); 
}); 

emitter.on( 'build', function( o ) {
  logic.build( o ).then( function( o ) {
    emitter.emit( 'run', o );
  })
  .catch( function() {
    console.log( 'build failed' );
  });
});

emitter.on( 'generate', function( o ) {
  logic.generate( o ).then( function( o ) {
    emitter.emit( 'build', o );
  });
});

emitter.on( 'traverse', function( o ) {
  logic.traverse( o ).then( function( o ) {
    base.traverse( o, function(defFile) {
      o['defFile'] = defFile;
      emitter.emit( 'generate', o );
    });
  });
});

base = new Base(program);
logic = new Logic( base );

emitter.emit( 'traverse', { testDir: program.path } );
