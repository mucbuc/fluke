{
	'includes': [
		'lib/ohm/ohm.gypi'
	],
	'target_defaults': {
		'include_dirs': [
			'.'
		],
		'sources': [
			'src/lexer.h',
			'src/lexer.hxx'
		],
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}
}