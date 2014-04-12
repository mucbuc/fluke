namespace om636
{
	namespace fluke
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
	    // parser<T> 
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		brute_parser<T, U>::brute_parser( context_type & c )
	    : m_context( c )
		{}

		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::context() -> context_type &
		{	return m_context; }

		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::context() const -> const context_type & 
		{	return m_context; }
		
		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::interpret(analyzer_type & analyzer) -> context_type & 
		{
			typedef typename analyzer_type::callback_type callback_type; 
			typedef typename callback_type::argument_type argument_type;

			auto onFunction( [&](const argument_type & value){
				analyzer.emit( "token", value );
			} );

			m_listener.push_back( analyzer.on( " ", onFunction ) );
			m_listener.push_back( analyzer.on( "\n", onFunction ) );
			m_listener.push_back( analyzer.on( "\t", onFunction ) );
			m_listener.push_back( analyzer.on( ";", onFunction ) );

	        return context();
		}
	} 	// fluke
} 	// om636


			// auto t( m_lexer.current() );
	  //       while(t)
	  //       {
	  //           context_type::state(context())->on_token( context(), m_lexer.current() );
	  //           t = m_lexer.next();
	  //       }
	// /////////////////////////////////////////////////////////////////////////////////////////////
	// template<class T>
	// template<class U>
	// void token<T>::read_next( U & in, char & front )
	// {
	// 	while (isspace(front))
	// 		if (!in.get(front))
	// 		{
	// 			m_type = terminator;
	// 			return;		
	// 		}

	// 	enum { period = '.', semicolon = ';' };
	// 	if (isalpha(front))
	// 	{
	// 		m_type = variable;                          // every alphabetic is a variable ??? 
	// 		do
	// 			m_name.push_back(front);
	// 		while (in.get(front) && isalpha(front) ); // this seems arbitrary, what about the variables names including numbers
	// 	}
	// 	else if (isdigit(front) || front == period)
	// 	{	
	// 	#ifdef NDEBUG
	// 		bool _period( front == period );
	// 	#endif 

	// 		m_type = number;

	// 		do
	// 		{		
	// 		#ifdef NDEBUG	
	// 			ASSERT( !_period || front != period );
	// 			_period = front == period;
	// 		#endif 	

	// 			m_name.push_back(front);
	// 			in.get(front);
	// 		}
	// 		while (isdigit(front) || front == period);
	// 	}
	// 	else if (front == semicolon)
	// 		m_type = terminator;
	// 	else
	// 	{ 
	// 		m_type = _operator;
	// 		m_name.push_back(front);
	// 		in.get(front);
	// 	}
	// }
