#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Classe que representa um cliente do banco
class Cliente {
private:
    string nome;
    string cpf;
public:
    // Construtor que inicializa nome e cpf
    Cliente(string nome, string cpf) {
        this->nome = nome;
        this->cpf = cpf;
    }
    // Métodos getters para acessar nome e cpf
    string getNome() const {
        return nome;
    }
    string getCpf() const {
        return cpf;
    }
};

// Classe que representa uma conta bancária
class ContaBancaria {
private:
    int numero;
    double saldo;
    Cliente titular;
public:
    // Construtor que inicializa número, titular e saldo (padrão zero)
    ContaBancaria(int numero, Cliente titular, double saldo = 0.0) : titular(titular) {
        this->numero = numero;
        this->saldo = saldo;
    }

    // Métodos getters
    int getNumero() const {
        return numero;
    }

    double getSaldo() const {
        return saldo;
    }

    Cliente getTitular() const {
        return titular;
    }

    // Método para depositar um valor na conta
    void depositar(double valor) {
        saldo += valor;
        cout << "Depositado: R$ " << valor << " na conta " << numero << endl;
    }

    // Método para sacar um valor da conta
    void sacar(double valor) {
        if (valor <= saldo) {
            saldo -= valor;
            cout << "Sacado: R$ " << valor << " da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente na conta " << numero << " para sacar R$ " << valor << endl;
        }
    }

    // Método para transferir um valor para outra conta
    void transferir(double valor, ContaBancaria &destino) {
        if (valor <= saldo) {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero << " para a conta " << destino.numero << endl;
        } else {
            cout << "Saldo insuficiente na conta " << numero << " para transferir R$ " << valor << endl;
        }
    }

    // Sobrecarga do método transferir para duas contas destino
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        if (valor <= saldo) {
            double valorDividido = valor / 2.0;
            saldo -= valor;
            destino1.depositar(valorDividido);
            destino2.depositar(valorDividido);
            cout << "Transferido: R$ " << valorDividido << " para cada conta (" << destino1.numero << " e " << destino2.numero << ") da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente na conta " << numero << " para transferir R$ " << valor << endl;
        }
    }

    // Método que exibe o saldo atual da conta
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    // Método que exibe as informações do titular e da conta
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }
};

// Função para pausar a tela
void pausar() {
    cout << "Pressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função principal
int main() {
    vector<Cliente> clientes;
    vector<ContaBancaria> contas;
    int opcao;

    do {
        cout << "\n=== Sistema Bancário ===\n";
        cout << "1. Cadastrar Cliente\n";
        cout << "2. Abrir Conta\n";
        cout << "3. Depositar\n";
        cout << "4. Sacar\n";
        cout << "5. Transferir\n";
        cout << "6. Exibir Saldo\n";
        cout << "7. Exibir Informações da Conta\n";
        cout << "8. Listar Contas\n";
        cout << "9. Listar Clientes\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        // Limpar o buffer do cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
        case 1: {
            // Cadastrar Cliente
            string nome, cpf;
            cout << "Digite o nome do cliente: ";
            getline(cin, nome);
            cout << "Digite o CPF do cliente: ";
            getline(cin, cpf);
            clientes.push_back(Cliente(nome, cpf));
            cout << "Cliente cadastrado com sucesso!\n";
            pausar();
            break;
        }
        case 2: {
            // Abrir Conta
            if (clientes.empty()) {
                cout << "Nenhum cliente cadastrado. Cadastre um cliente primeiro.\n";
            } else {
                int numCliente;
                double saldoInicial;
                cout << "Clientes disponíveis:\n";
                for (size_t i = 0; i < clientes.size(); ++i) {
                    cout << i + 1 << ". " << clientes[i].getNome() << ", CPF: " << clientes[i].getCpf() << endl;
                }
                cout << "Selecione o número do cliente: ";
                cin >> numCliente;

                if (numCliente > 0 && numCliente <= static_cast<int>(clientes.size())) {
                    cout << "Digite o saldo inicial (ou zero): ";
                    cin >> saldoInicial;

                    int numeroConta = 1000 + contas.size() + 1; // Gerar número de conta
                    contas.push_back(ContaBancaria(numeroConta, clientes[numCliente - 1], saldoInicial));
                    cout << "Conta número " << numeroConta << " aberta com sucesso!\n";
                } else {
                    cout << "Cliente inválido.\n";
                }
            }
            pausar();
            break;
        }
        case 3: {
            // Depositar
            int numeroConta;
            double valor;
            cout << "Digite o número da conta: ";
            cin >> numeroConta;
            cout << "Digite o valor a depositar: ";
            cin >> valor;

            bool encontrado = false;
            for (auto &conta : contas) {
                if (conta.getNumero() == numeroConta) {
                    conta.depositar(valor);
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Conta não encontrada.\n";
            }
            pausar();
            break;
        }
        case 4: {
            // Sacar
            int numeroConta;
            double valor;
            cout << "Digite o número da conta: ";
            cin >> numeroConta;
            cout << "Digite o valor a sacar: ";
            cin >> valor;

            bool encontrado = false;
            for (auto &conta : contas) {
                if (conta.getNumero() == numeroConta) {
                    conta.sacar(valor);
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Conta não encontrada.\n";
            }
            pausar();
            break;
        }
        case 5: {
            // Transferir
            int numeroOrigem, numeroDestino1, numeroDestino2;
            double valor;
            cout << "Digite o número da conta de origem: ";
            cin >> numeroOrigem;
            cout << "Digite o valor a transferir: ";
            cin >> valor;

            ContaBancaria *contaOrigem = nullptr;
            ContaBancaria *contaDestino1 = nullptr;
            ContaBancaria *contaDestino2 = nullptr;

            for (auto &conta : contas) {
                if (conta.getNumero() == numeroOrigem) {
                    contaOrigem = &conta;
                    break;
                }
            }

            if (contaOrigem) {
                cout << "Digite o número da conta de destino: ";
                cin >> numeroDestino1;

                for (auto &conta : contas) {
                    if (conta.getNumero() == numeroDestino1) {
                        contaDestino1 = &conta;
                        break;
                    }
                }

                if (contaDestino1) {
                    cout << "Deseja adicionar uma segunda conta de destino? (s/n): ";
                    char opcao;
                    cin >> opcao;

                    if (opcao == 's' || opcao == 'S') {
                        cout << "Digite o número da segunda conta de destino: ";
                        cin >> numeroDestino2;

                        for (auto &conta : contas) {
                            if (conta.getNumero() == numeroDestino2) {
                                contaDestino2 = &conta;
                                break;
                            }
                        }

                        if (contaDestino2) {
                            contaOrigem->transferir(valor, *contaDestino1, *contaDestino2);
                        } else {
                            cout << "Segunda conta de destino não encontrada.\n";
                        }
                    } else {
                        contaOrigem->transferir(valor, *contaDestino1);
                    }
                } else {
                    cout << "Conta de destino não encontrada.\n";
                }
            } else {
                cout << "Conta de origem não encontrada.\n";
            }
            pausar();
            break;
        }
        case 6: {
            // Exibir Saldo
            int numeroConta;
            cout << "Digite o número da conta: ";
            cin >> numeroConta;

            bool encontrado = false;
            for (const auto &conta : contas) {
                if (conta.getNumero() == numeroConta) {
                    conta.exibirSaldo();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Conta não encontrada.\n";
            }
            pausar();
            break;
        }
        case 7: {
            // Exibir Informações da Conta
            int numeroConta;
            cout << "Digite o número da conta: ";
            cin >> numeroConta;

            bool encontrado = false;
            for (const auto &conta : contas) {
                if (conta.getNumero() == numeroConta) {
                    conta.exibirInformacoes();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Conta não encontrada.\n";
            }
            pausar();
            break;
        }
        case 8: {
            // Listar Contas
            if (contas.empty()) {
                cout << "Nenhuma conta cadastrada.\n";
            } else {
                for (const auto &conta : contas) {
                    conta.exibirInformacoes();
                    cout << "---------------------------\n";
                }
            }
            pausar();
            break;
        }
        case 9: {
            // Listar Clientes
            if (clientes.empty()) {
                cout << "Nenhum cliente cadastrado.\n";
            } else {
                for (const auto &cliente : clientes) {
                    cout << "Nome: " << cliente.getNome() << ", CPF: " << cliente.getCpf() << endl;
                }
            }
            pausar();
            break;
        }
        case 0:
            cout << "Saindo do sistema...\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
            pausar();
            break;
        }
    } while (opcao != 0);

    return 0;
}