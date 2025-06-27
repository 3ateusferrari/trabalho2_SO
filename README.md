# Simulador de Gerenciamento de Memória com Paginação

Este projeto simula o gerenciamento de memória usando paginação, conforme especificado no Trabalho 2 de SO.

## Compilação

Para compilar o projeto, utilize:

```
make
```

## Execução

Após compilar, execute:

```
./simulador
```

## Funcionalidades
- Visualizar memória física
- Criar processo
- Visualizar tabela de páginas de um processo

## Configuração
Ao iniciar, o programa solicitará:
- Tamanho da memória física (bytes)
- Tamanho da página/quadro (bytes)
- Tamanho máximo de um processo (bytes)

## Organização
- `main.c`: Menu principal
- `memoria.c/h`: Gerenciamento da memória física
- `processo.c/h`: Gerenciamento de processos