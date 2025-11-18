# To build

Using docker to build:

```
sudo docker build -t cube .
sudo docker run -it --rm -v ./:/out cube
```

If you get errors when executing the binary, you need to install libraries:

```
sudo pacman -S mesa glu glfw glew libx11 libxcb libxau libxdmcp
```

Or manually:
```bash
cmake .
make
```

Usage:

- `e`: Make the cube change colors
- `r`: Rotate the cube
- `wasd`: Move the camera
- `space`: Move up
- `shift`: Move down


Défi:
> Modéliser et afficher en OpenGL un objet 3D (au choix) avec pipeline moderne (VBO/VAO, shaders) et options visuelles.
>
> Un cube Une sphère prisme à base hexagonale
>
>règles Fournir un dockerfile et/ou docker compose qui contient et exécute le code et rend la visualisation accessible sous une forme quelconque et un readme sur comment accéder le tout
>
>Techniques : OpenGL core (3.3+), GLSL, VAO/VBO, indices, caméra orbit, transformations (MVP).
>
>Rendu : Phong ou Blinn-Phong (au minimum), source(s) de lumière, shading fragment.
>
>Options bonus : textures, ombres, skybox.
>
>Livrables : Fournir un dockerfile et/ou docker compose qui contient et exécute le code et rend la visualisation accessible sous une forme quelconque et un readme sur comment accéder le tout

