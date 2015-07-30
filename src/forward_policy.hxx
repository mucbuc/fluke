namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // forward_policy<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    template<class V>
    typename forward_policy<T>::value_type forward_policy<T>::on_init(V &)
    {
        return value_type(); 
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    template<class V, class W>
    typename forward_policy<T>::value_type forward_policy<T>::on_init(V &, const W & i)
    {
        return value_type( i );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    template<class V>
    V forward_policy<T>::to_value(const context_type & c)
    {
        return c.value_ref(); 
    }
    
    // comparisons
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    bool forward_policy<T>::on_equal(const context_type & lhs, const context_type & rhs) const
    {
        return lhs.value_ref() == rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    int forward_policy<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
    {
        return lhs.value_ref() - rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    int forward_policy<T>::on_sign(const context_type & lhs) const
    {
        return om636::sign( lhs.value_ref() ); 
    }
    
    // modifiers
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_swap(context_type & lhs, context_type & rhs) const
    {
        using om636::swap;
        using std::swap;
        
        swap( lhs.value_ref(), rhs.value_ref() );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_add(context_type & lhs, const context_type & rhs) const
    {
        lhs.value_ref() += rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_subtract(context_type & lhs, const context_type & rhs) const
    {
        lhs.value_ref() -= rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_mult(context_type & lhs, const context_type & rhs) const
    {
        lhs.value_ref() *= rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_divide(context_type & lhs, const context_type & rhs) const
    {
        lhs.value_ref() /= rhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_remainder(context_type & lhs, const context_type & rhs) const
    {
        lhs.value_ref() %= lhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_inc(context_type & lhs) const
    {
        ++lhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_dec(context_type & lhs) const
    {
        --lhs.value_ref();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
    void forward_policy<T>::on_invert(context_type & lhs) const
    {
        lhs.value_ref() = value_type( 1 ) / lhs.value_ref();
    }
    
}   // om636
