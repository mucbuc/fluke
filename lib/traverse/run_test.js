#!/usr/bin/env node
require( 'child_process' )
.fork( './test/plank/bin/test.js' );