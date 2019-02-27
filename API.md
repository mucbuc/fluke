## namespace om636

### namespace fluke
    
#### struct splitter
_type signature_
```C++
template<class T, class U = typename T::value_type::value_type>
``` 

```C++
template<class V, class W>
static void split(
                       V &,
                       std::function<bool(char_type)>,
                       std::function<void(token_type)>,
                       W &);
```
```C++
template<class V>
static void split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(token_type)>);
```

#### struct buffered_splitter
```C++
template<class V>
static void split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type, const_iterator, const_iterator)>,
                     U &);
```
```C++            
template<class V>
static void split(
                     V &,
                     std::function<bool(char_type)>,
                     std::function<void(char_type, const_iterator, const_iterator)>);
```