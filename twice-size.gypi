{
	'target_defaults': {
		'include_dirs': [
			'.'
		],
		'sources': [
			'src/pset.h',
			'src/pset.hxx',
			'src/queue.h',
			'src/queue.hxx',
			'src/stack.h',
			'src/stack.hxx',
		], #sources
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	},
}