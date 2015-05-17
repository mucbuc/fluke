{
	'target_defaults': {
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}, #target_defaults
	'conditions': [
		[ 
			'OS=="mac"', {
				'xcode_settings': {
					'OTHER_CFLAGS': [
						'-std=c++11', '-stdlib=libc++'
					],
				}#xcode-settings
			} #mac
		],
	] #conditions
}