{
	'includes':[
		'lib/fluke/fluke.gypi',
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'src/json_parser.h',
			'src/lexer.h',
			'src/main.cpp',
		], #sources
		'include_dirs': [
			'.'
		], #include_dirs		
	}, #target_defaults
}