# Zappy

A multiplayer game server where AI players try to survive, with a graphical client to watch the game.

## Components
| Folder | Language | Binary | Role |
|---|---|---|---|
| `ZappyServer/` | C | `zappy` | Game server |
| `ZappyGUI/` | C++11 + SFML | `zappy_gui` | Graphical client |
| `ZappyIA/` | C++ | `clientIA` | AI client |

The AI reads its connection settings from `ZappyIA/config.xml` (default `127.0.0.1:4242`).

## Requirements
`gcc`, `g++`, `make`, and [SFML](https://www.sfml-dev.org/) (graphics, window, system, audio).

## Build
```bash
make          # everything
make server   # or: make gui / make ia
make clean    # or: make fclean
```

## Status
Archived, no further development planned.

## License
MIT