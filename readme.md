# Word Brick (Raylib)

> Jogo desenvolvido em C utilizando a biblioteca [raylib](https://www.raylib.com/).

---

## Sumário

- [Pré-requisitos](#pré-requisitos)
- [Instalação e Execução Local](#instalação-e-execução-local)
- [Execução com Docker](#execução-com-docker)
- [Observações](#observações)

---

## Pré-requisitos

- **CMake** versão **3.27.7** (ou superior)
- Compilador C compatível (ex: gcc)
- Dependências da biblioteca [raylib](https://www.raylib.com/)

---

## Instalação e Execução Local

1. **Clone o repositório:**
   ```bash
   git clone <url-do-repositorio>
   cd ProjetoPI
   ```

2. **Compile o projeto (na raiz):**
   ```bash
   make
   ```
   O executável `game` será gerado na raiz do projeto.

3. **Execute o jogo:**
   ```bash
   ./game
   ```

---

## Execução com Docker

1. **Construa a imagem Docker:**
   ```bash
   docker build -t word-brick-raylib .
   ```

2. **Execute o container com suporte a áudio e interface gráfica:**
   ```bash
   docker run --rm -it \
      -e DISPLAY=$DISPLAY \
      -v /tmp/.X11-unix:/tmp/.X11-unix \
      -v /run/user/$(id -u)/pulse:/run/user/$(id -u)/pulse \
      -e PULSE_SERVER=unix:/run/user/$(id -u)/pulse/native \
      word-brick-raylib
   ```

---

## Observações

- Certifique-se de que o CMake está instalado e na versão correta:
  ```bash
  cmake --version
  ```
- Caso precise instalar o CMake 3.27.7:
  ```bash
  sudo apt-get update
  sudo apt-get install cmake=3.27.7*
  ```
  (ou siga as instruções do site oficial para outras plataformas)
- O projeto utiliza a biblioteca [raylib](https://www.raylib.com/). Certifique-se de que as dependências necessárias estão instaladas.