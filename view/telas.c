#include "telas.h"
#include "../lcurses.h"
#include "../model/tables.h"
#include "utils.h"
#include <stdlib.h>

int menu_principal() {
    while (1) {
        clrscr();
        switch (menu(5, "Cadastros", "Gestão de Estoque", "Reservas", "Relatórios", "Sair")) {
        case 0:
            menu_cadastros();
            break;
        case 1:
            // menu_produtos();
            break;
        case 2:
            menu_reservas();
            break;
        case 3:
            // menu_relatorios();
            break;
        default: // Sair
            return EXIT_SUCCESS;
        }
    }
}

int menu_cadastros() {
    while (1) {
        clrscr();
        switch (menu(8, "Hóspedes", "Hotel", "Categorias de acomodações", "Operadores", "Acomodações", "Produtos", "Fornecedores", "Voltar")) {
        case 0:
            menu_hospedes();
            break;
        case 1:
            menu_hotel();
            break;
        case 2:
            menu_categoria();
            break;
        case 3:
            menu_operador();
            break;
        case 4:
            menu_acomodacao();
            break;
        case 5:
            menu_produto();
            break;
        case 6:
            menu_fornecedor();
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int menu_hospedes() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir hóspede", "Ver hóspede", "Voltar")) {
        case 0:
            cadastrar_hospede();
            break;
        case 1:
            ver_hospede();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_hospede() {
    clrscr(); // Sempre limpar a tela ...

    struct Hospede hosp = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hospedes, &hosp); // Modo 0 = Inserir

    DATABASE->open(Hospedes);
    DATABASE->insert(Hospedes, &hosp); // Insere o hóspede no banco de dados
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int ver_hospede() {
    DATABASE->open(Hospedes);

    DATABASE_forEach(struct Hospede, hosp, Hospedes) {
        clrscr();
        form(1, Hospedes, &hosp);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr();
            form(2, Hospedes, &hosp);
            DATABASE->update(Hospedes, &hosp);
            break;
        case 2:
            DATABASE->delete (Hospedes);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Hospedes);
}

int menu_hotel() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir hotel", "Ver hotel", "Voltar")) {
        case 0:
            cadastrar_hotel();
            break;
        case 1:
            ver_hotel();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_hotel() {
    clrscr();

    struct Hotel hotel = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hoteis, &hotel); // Modo 0 = Inserir

    DATABASE->open(Hoteis);
    DATABASE->insert(Hoteis, &hotel); // Insere o hotel no banco de dados
    DATABASE->close(Hoteis);
    return EXIT_SUCCESS;
}

int ver_hotel() {
    DATABASE->open(Hoteis);

    DATABASE_forEach(struct Hotel, hotel, Hoteis) {
        clrscr();
        form(1, Hoteis, &hotel);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr();
            form(2, Hoteis, &hotel);
            DATABASE->update(Hoteis, &hotel);
            break;
        case 2:
            DATABASE->delete (Hoteis);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Hoteis);
}

int menu_categoria() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir categoria", "Ver categoria", "Voltar")) {
        case 0:
            cadastrar_categoria();
            break;
        case 1:
            ver_categoria();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_categoria() {
    clrscr();

    struct Categoria categ = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Categorias, &categ); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Categorias);
    DATABASE->insert(Categorias, &categ); // Insere a categoria no banco de dados
    DATABASE->close(Categorias);
    return EXIT_SUCCESS;
}

int ver_categoria() {
    DATABASE->open(Categorias);

    DATABASE_forEach(struct Categoria, cat, Categorias) {
        clrscr();
        form(1, Categorias, &cat);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Categorias, &cat);
            DATABASE->update(Categorias, &cat);
            break;
        case 2:
            DATABASE->delete (Categorias);
            break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Categorias);
}

int menu_operador() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir operador", "Ver operador", "Voltar")) {
        case 0:
            cadastrar_operador();
            break;
        case 1:
            ver_operador();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_operador() {
    clrscr();

    struct Operador ope = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Operadores, &ope);

    DATABASE->open(Operadores);
    DATABASE->insert(Operadores, &ope);
    DATABASE->close(Operadores);
    return EXIT_SUCCESS;
}

int ver_operador() {
    DATABASE->open(Operadores);

    DATABASE_forEach(struct Operador, ope, Operadores) {
        clrscr();
        form(1, Operadores, &ope);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Operadores, &ope);
            DATABASE->update(Operadores, &ope);
            break;
        case 2:
            DATABASE->delete (Operadores);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Operadores);
}

int menu_acomodacao() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir acomodação", "Ver acomodação", "Voltar")) {
        case 0:
            cadastrar_acomodacao();
            break;
        case 1:
            ver_acomodacao();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_acomodacao() {
    clrscr();

    struct Acomodacao acomo = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Acomodacoes, &acomo); // Modo 0 = Inserir

    DATABASE->open(Acomodacoes);
    DATABASE->insert(Acomodacoes, &acomo);
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}

int ver_acomodacao() {
    DATABASE->open(Acomodacoes);

    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        form(1, Acomodacoes, &acom);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Acomodacoes, &acom);
            DATABASE->update(Acomodacoes, &acom);
            break;
        case 2:
            DATABASE->delete (Acomodacoes);
            break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Acomodacoes);
}

int menu_produto() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir produto", "Ver produto", "Voltar")) {
        case 0:
            cadastrar_produto();
            break;
        case 1:
            ver_produto();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_produto() {
    clrscr();

    struct Produto prod = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Produtos, &prod);

    DATABASE->open(Produtos);
    DATABASE->insert(Produtos, &prod);
    DATABASE->close(Produtos);
    return EXIT_SUCCESS;
}

int ver_produto() {
    DATABASE->open(Produtos);

    DATABASE_forEach(struct Produto, prod, Produtos) {
        clrscr();
        form(1, Produtos, &prod);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Produtos, &prod);
            DATABASE->update(Produtos, &prod);
            break;
        case 2:
            DATABASE->delete (Produtos);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Produtos);
}

int menu_fornecedor() {
    while (1) {
        clrscr();
        switch (menu(3, "Inserir Fornecedor", "Ver Fornecedor", "Voltar")) {
        case 0:
            cadastrar_fornecedor();
            break;
        case 1:
            ver_fornecedor();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_fornecedor() {
    clrscr();

    struct Fornecedor forn = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Fornecedores, &forn);

    DATABASE->open(Fornecedores);
    DATABASE->insert(Fornecedores, &forn);
    DATABASE->close(Fornecedores);
    return EXIT_SUCCESS;
}

int ver_fornecedor() {
    DATABASE->open(Fornecedores);

    DATABASE_forEach(struct Fornecedor, forn, Fornecedores) {
        clrscr();
        form(1, Fornecedores, &forn);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Fornecedores, &forn);
            DATABASE->update(Fornecedores, &forn);
            break;
        case 2:
            DATABASE->delete (Fornecedores);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Fornecedores);
}
int menu_reservas() {
    while (1) {
        clrscr();
        switch (menu(3, "Verificar reserva", "Inserir reserva", "Ver reserva", "Voltar")) {
        case 0:
            // verificar_reserva();
            break;
        case 1:
            cadastrar_reserva();
            break;
        case 2:
            ver_reserva();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}
int cadastrar_reserva() {
    clrscr();
    //Recupera os dados da reserva
    struct Reserva reserva = {};
    form(0, Reservas, &reserva);

    //Cria a reserva
    DATABASE->open(Reservas);
    DATABASE->insert(Reservas, &reserva);
    DATABASE->close(Reservas);

    return EXIT_SUCCESS;
}

int ver_reserva() {
    DATABASE->open(Reservas);

    DATABASE_forEach(struct Reserva, reserva, Reservas) {
        clrscr();
        form(1, Reservas, &reserva);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Reservas, &reserva);
            DATABASE->update(Reservas, &reserva);
            break;
        case 2:
            DATABASE->delete (Reservas);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Reservas);
}
