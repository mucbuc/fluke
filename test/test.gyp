{
	'includes':[
		'lib/ohm/ohm.gypi',
		'../fluke.gypi',
		'plank/def/mac-targets.gypi',
		'plank/def/cpp11.gypi'
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'../test/src/main.cpp',
			#'../test/src/test.h',
			'../test/src/lexer.h'
		], #sources
		'include_dirs': [
			'plank/src/',
			'../test/'
		], #include_dirs		
	}, #target_defaults
}