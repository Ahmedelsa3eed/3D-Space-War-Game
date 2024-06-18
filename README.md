# 3D Space War Game

Welcome to the 3D Space War Game, an immersive space battle experience developed using OpenGL. The game enables users from controlling spacecraft to explore the solar system while being attacked by enemy spacecrafts. It uses two view ports: One for spacecraft (first person view) and the other for the whole solar system (See figure 1 for more declaration).

![window](image.png)

## Demo
https://youtu.be/Muua5_27-84

## Features

- **Instantiation of Sun and 8 planets**
- **Solar system animation**: spinning and rotation of planets around Sun and Moon around Earth
- **User spacecraft** instantiation, movement, shooting, and health.
- **Enemy spacecrafts** instantiation, movement, shooting, and health.
- **Spacecrafts projectiles** instantiation, and movement.
- **Pickable objects instantiation and its effects**: upgrading weapons, increasing health, etc.
- **UI System**: Menus, Health bars, etc.
- **Collision Detection**: Spacecraft with projectile, Spacecraft with planet/Sun, Spacecraft with pickable objects.
- **Scoring System**
- **Sound effects**: UI, Shooting, Destroying, etc.
- **Visual effects**: Shooting, Destroying, Collision, etc.
- **Planets and spacecrafts textures**
- **Survival mode**: play the game until your health drops to 0.
- **Time attack mode**: destroy all enemies before the time passes.

## Getting Started

### Prerequisites

- freeglut
- GLEW
- glut
- GLU
- SOIL

### Installation

1. Clone the repository:
    ```bash
    https://github.com/Ahmedelsa3eed/3D-Space-War-Game.git
    ```
2. Navigate to the project directory:
    ```bash
    cd 3D-Space-War-Game
    ```
3. Build the project:

    - for Windows users:
        ```bash
        .\build.cmd
        ```
    - for Linux users:
        ```bash
        ./build.sh
        ```
4. Run the game:
    ```bash
    ./main
    ```

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


Thank you for checking out the 3D Space War Game. We hope you enjoy playing it as much as we enjoyed making it!