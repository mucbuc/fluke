{
	'includes':[
		'lib/twice-size/twice-size.gypi'
	],
	'target_defaults': {
		'sources': [
			'src/agent.h',
			'src/agent.hxx',
			'src/emitter.h',
			'src/emitter.hxx',
			'src/listener.h',
			'src/listener.hxx',
			'src/quemitter.h',
			'src/quemitter.hxx'
		],
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}
}