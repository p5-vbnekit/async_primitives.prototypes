# p5-async_primitives
`C++ 17` library with asynchronous primitives (prototype state).

## Hello, world
```cpp
::ap::event::Dispatcher<::std::string_view> dispatcher_;

dispatcher_.subscribe([&] (auto const &event) {
    application_.log << event;
});

application_.on_ready([dispatcher_ = ::std::move(dispatcher_)] {
    dispatcher_.dispatch("Hello, world!");
});
```

## Basic primitives
1. **Event dispatcher** & **Event source**: \
   yet another `signal/slot` implementation \
   with **Shared Subscripton** ("weak"|"strong") entity as `Connection`
3. **Promise** & **Future**: not implemented yet
4. **Coroutines adapters**: not implemented yet

## Examples
Check out [examples directory](./examples).

## $${\color{red}WARNING}$$
This is unstable prototype and any things (commit history, api, abi, etc) may be changed.
