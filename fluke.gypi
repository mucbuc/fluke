{
	'includes': [
		'lib/ohm/ohm.gypi',
		'lib/om636/om636.gypi'
	],
	'target_defaults': {
		'include_dirs': [
			'.'
		],
		'sources': [
			'src/flukefwd.h',
			'src/lexer.h',
			'src/lexer.hxx',
			'src/parser.h',
			'src/parser.hxx',
		],
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}
}