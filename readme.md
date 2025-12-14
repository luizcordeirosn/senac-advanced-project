## Como executar o projeto

### Pré-requisitos
- **CMake** versão **3.27.7** (ou superior)
- Compilador C compatível (ex: gcc)

### Passo a passo
1. **Clone o repositório** (se ainda não fez):
	```bash
	git clone <url-do-repositorio>
	cd ProjetoPI
	```

2. **Compile o projeto** (na raiz do projeto):
	```bash
	make
	```
	Isso irá gerar o executável `game` na raiz do projeto.

3. **Execute o jogo**:
	```bash
	./game
	```

### Observações
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