# Flight Data Plotter

## Overview
The Flight Data Plotter is a C++ program utilizing ImGui and ImPlot libraries to provide a user-friendly interface for visualizing flight data. This tool allows users to plot various parameters and analyze flight information in a graphical manner. The program is built using the Conan package manager and CMake for easy dependency management and compilation.

## Features
- **Interactive Interface**: Powered by ImGui, the program offers a sleek and interactive user interface.
- **Real-time Plotting**: ImPlot enables real-time plotting of flight data, ensuring up-to-date visualizations.
- **Customizable Plots**: Users can customize plots by selecting parameters, adjusting colors, and configuring plot settings.
- **Data Export**: Easily export flight data files in common formats for seamless analysis.

## Requirements
- C++ compiler with C++11 support
- Conan package manager
- CMake

## Getting Started
1. Clone the repository.
2. Install dependencies using Conan.

```bash
conan install . --build=missing
```
for a debug version you can add `--settings=build_type=Debug`

3. Configure and build the project with CMake.

```bash
cmake --preset conan-release
cmake --build --preset conan-release
```

for a debug version you can use `conan-debug`

4. Run the executable.

```bash
./build/Release/flight_data_plotter
```

## Contributing
Feel free to contribute by submitting bug reports, feature requests, or pull requests. Your feedback and contributions are highly appreciated.

## License
This Flight Data Plotter is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```mermaid
classDiagram

class UIWidget {
  + print()
}

class App {
  - window_list
  - window
  - context
  + setup()
  + process_events()
  + update()
  + close()
}

class GlobalWindow {
  - widget_list
  + add_widget()
  + display()
}

class SensorData {
  + time
  + acceleration
  + rotation
  + magnetic
}

class NetworkReceiver {
  + display()
  - update_data()
  - hostname
  - ssid
  - wireless_enabled
  - networkmanager_proxy
  - data_client
}

class NetworkManagerProxy {
  + wireless_enabled()
  + hostname()
  + network_name()
  - get_wireless_device_path()
  - set_wireless_device()
  - networkmanager_proxy
  - wireless_device_proxy
  - settings_proxy
}

class NetworkManagerDBUSProxy {
  + read_parameter()
  + read_type()
  - dbus_proxy
}

class AsyncServer {
  + do_receive()
  + handle_read()
  - socket
  - data
}

class DataClient {
  - io_context
  - server
}

class Graph {
  - recording
  - data_queue
  + print()
  + start_recording()
  + stop_recording()
  + clear_graph()
}

class DataStorage {
  - acceleration: vector
  - rotation: vector
  - magnetic: vector
  + add_point()
  + export()
}

class Visualisation {
  - model
  - background
  - orientation
}

class ControlPanel {
  + print()
  + send_message()
}

class Controller {
  + send_message()
}

class MadgFilter {
  + currentData
  + previousData
  + filter()
}

App --> GlobalWindow

GlobalWindow --> Visualisation
GlobalWindow --> NetworkReceiver
GlobalWindow --> Graph
GlobalWindow --> ControlPanel

NetworkReceiver --* NetworkManagerProxy
NetworkReceiver --* DataClient
DataClient --* AsyncServer
NetworkManagerProxy --* NetworkManagerDBUSProxy

UIWidget --|> NetworkReceiver
UIWidget --|> ControlPanel
UIWidget --|> Graph

DataStorage "1" --* "0..*" SensorData
Graph --> DataStorage
NetworkReceiver --> DataStorage
DataStorage --> MadgFilter

ControlPanel --> Controller
```
