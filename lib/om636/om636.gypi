{
	'target_defaults': {
		'include_dirs': [
			'.'
		], #include_dirs
		'sources': [ 
			'src/components/componentsfwd.h',
			'src/components/context.h',
			'src/components/context.hxx',
			'src/components/observer.h',
			'src/components/observer.hxx',
			'src/components/range.h',
			'src/components/subject.h',
			'src/components/subject.hxx',
			'src/core/assert.cpp', 
			'src/core/assert.h',
			'src/core/assert.hxx',
			'src/core/chain.h',
			'src/core/chain.hxx',
			'src/core/constraints.h',
			'src/core/constraints.hxx',
			'src/core/core.h',
			'src/core/core.hxx',
			'src/core/corefwd.h',
			'src/core/persistent.h',
			'src/core/persistent.hxx',
			'src/core/tests.h',
			'src/core/tests.hxx',
			'src/core/traverse.h',
			'src/core/traverse.hxx',
			'src/core/typetraits.h',
			'src/core/typeutills.h',
			'src/create/abstract_factory.h',
			'src/create/abstract_factory.hxx',
			'src/create/concrete_factory.h',
			'src/create/concrete_factory.hxx',
			'src/create/createfwd.h',
			'src/create/object_factory.h',
			'src/create/object_factory.hxx',
			'src/create/singleton.h',
			'src/create/singleton.hxx',
		], #sources
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}
}