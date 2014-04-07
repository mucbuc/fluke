{
	'targets': [
		{
			'target_name': 'test', 
			'type': 'executable',
			'sources': [
				'src/emitter.cpp'
			],
			'includes':[
				'../lib/twice-size/twice-size.gypi'
			],
			'include_dirs': [
				'src/',
				'../../',
				'../lib/twice-size/'
			],
			'conditions': [
				[
					'OS=="mac"', {
						'xcode_settings': {
		        			'OTHER_CFLAGS': [
		          				'-std=c++11', '-stdlib=libc++'
		        			],
		        		}
					}, {
						'cflags': [
							'-std=c++11', '-stdlib=libc++'
						]
					}		
				]
			]
        }
	]
}