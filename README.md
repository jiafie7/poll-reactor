# poll-reactor

I combined the [poll-based socket processing framework](https://github.com/jiafie7/poll) with the [C++ thread pool framework](https://github.com/jiafie7/posix-thread) to implement the poll-based Reactor model.

## 🖥️ Getting Started

1. Clone the Repository

```sh
git clone https://github.com/jiafie7/poll-reactor.git
cd poll-reactor
```

2. Build the Project

```sh
mkdir build && cd build
cmake ..
make

./server &

./client
```

## 📝 License

This project is licensed under the MIT License. See the LICENSE file for more information.

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome. Feel free to fork the repository, open issues, or submit pull requests.
