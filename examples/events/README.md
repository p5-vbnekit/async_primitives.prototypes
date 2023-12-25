# Examples / Events

Here you can find examples of using the `event::Dispatcher<T>: event::Source<T>` entity in following options:
1. [Easy](./src/easy.cxx)
2. [Hard](./src/hard.cxx)
3. [Nightmare](./src/nightmare.cxx)

### Dependencies
The library doesn't depend on anything. To simplify the examples, we use `Qt Event Loop` as async I/O machinery. Native `C++ coroutines`, `::bost::asyncio` (, etc.) may be used instead without any problems.
