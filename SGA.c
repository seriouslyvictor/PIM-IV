#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

#define MAX_LENGTH 100
#define MAX_MONTHS 12

#define USER_FILE "usuarios.txt"
#define COMPANY_FILE "empresas.txt"

// Estrutura para armazenar informações de uma empresa.
typedef struct
{
    char nome[100];
    char cnpj[20];
    char telefone[20];
    char rua[200];
    char bairro[200];
    char cidade[200];
    char estado[3];
    char cep[10];
    char email[100];
    int numMonths;
    char month[12][20];
    double wasteTreatment[12]; // Array for monthly waste treatment
    double cost[12];           // Array for monthly costs
} Company;

// Protótipos das funções, para que possam ser invocadas mesmo que sua definição venha após o ponto de chamada.
bool login(const char *username, const char *password);
void displayWelcomeMessage();
void mainMenu();
void registerCompany();
void editCompany();
void openReportsMenu();
void registerUser();
FILE *openFile(const char *filename, const char *mode);
void closeFile(FILE *file);
void getInput(const char *prompt, char *buffer, size_t size);
void listCompanies(char companyNames[][MAX_LENGTH], int *companyCount);
int selectCompany(int companyCount);
int reportByCompany();
bool processCompanyEdit(FILE *file, FILE *tempFile, const char *targetCompany);
void updateCompanyInfo(FILE *tempFile);
int loadCompanies(const char *filename, Company companies[], int maxCompanies);

// Função principal do programa.
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt_br.UTF-8"); // Configuração para acentos e caracteres especiais.

    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char choice[3];
    displayWelcomeMessage();
    // Validação do login
    while (1)
    {
        getInput("Digite o seu nome de usuário: ", username, MAX_LENGTH);
        getInput("Digite a sua senha: ", password, MAX_LENGTH);

        // Validação do login
        if (login(username, password))
        {
            printf("Login realizado com sucesso! Bem-vindo, %s.\n", username);
            mainMenu();
            break; // Exit the loop after successful login
        }
        else
        {
            printf("Falha no login. Verifique suas credenciais.\n");
            getInput("Deseja tentar novamente? (s/n): ", choice, sizeof(choice));
            if (choice[0] == 'n' || choice[0] == 'N')
            {
                printf("Encerrando o programa.\n");
                break; // Exit the loop if the user chooses not to retry
            }
        }
    }

    return 0;
}

// Função para abrir arquivos e tratar eventuais erros de abertura.
FILE *openFile(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);
    if (!file)
    {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", filename);
    }
    return file;
}

// Função para gerenciar fechamentos dos arquivos e tratar eventuais erros de fechamento.
void closeFile(FILE *file)
{
    if (file)
    {
        fclose(file);
    }
}

// Função para resgatar digitação do usuário
void getInput(const char *prompt, char *buffer, size_t size)
{
    printf("%s", prompt);
    scanf(" %[^\n]", buffer);
}

// Função para verificar se o usuário e senhae estão corretos.
bool login(const char *username, const char *password)
{
    FILE *file = openFile(USER_FILE, "r");
    if (!file)
    {
        return false;
    }

    char file_username[MAX_LENGTH];
    char file_password[MAX_LENGTH];

    while (fscanf(file, "%s %s", file_username, file_password) != EOF)
    {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
        {
            closeFile(file);
            return true;
        }
    }
    closeFile(file);
    return false;
}

void displayWelcomeMessage()
{
    printf("               .,aadd88888888bbaa,.\n");
    printf("             ,ad8888888888888888888888ba,\n");
    printf("          ,a888888888888888888888888888888a,\n");
    printf("        a888888888888888888888888888888888888a\n");
    printf("      a888888888888P\"    \"8,       `Y8888888888a\n");
    printf("     d888888888888'       )8,       `88888888888b\n");
    printf("    d888888888888'       ,888,        ,8888888888b\n");
    printf("   d888888888888'       ,88888a      ,888888888888b\n");
    printf("  I88888888888888ba,   ,88888P'     ,88888888888888I\n");
    printf(" ,88888888888\"    Y88ba88888888888'    `Y8888888888,\n");
    printf(" I888888888P       Y88888888888888P\"'    `Y888888888I\n");
    printf(" 888888888P         `8888888888888b       `Y888888888\n");
    printf(" 88888888P        ,d888888888888888b       )888888888\n");
    printf(" I88888888b      ,d88888888888888888b     ,d88888888I\n");
    printf(" `888888888b    ,d888888888888P 88888baaad8888888888'\n");
    printf("  I888888888b  ,8'        888P           d888888888I\n");
    printf("   Y888888888b,8'         88P           d888888888P\n");
    printf("    Y88888888888          88b          d888888888P\n");
    printf("     Y8888888888b,        888b        d888888888P\n");
    printf("      \"88888888888888888888888b 888888888888888\"\n");
    printf("        \"888888888888888888888888888888888888\"\n");
    printf("          `\"888888888888888888888888888888\"'\n");
    printf("             `\"Y8888888888888888888888P\"'\n");
    printf("                 ``\"\"YY88888888PP\"\"''\n");
    printf("\n");
    printf("            SISTEMA DE GESTÃO AMBIENTAL\n");
    printf("=============================================\n\n");
}

void mainMenu()
{
    int option;
    while (1)
    {
        printf("\n--- Menu Principal ---\n");
        printf("1 - Cadastrar Nova Empresa\n");
        printf("2 - Editar informações de uma Empresa\n");
        printf("3 - Gerar relatórios\n");
        printf("4 - Cadastrar novo usuário\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            registerCompany();
            break;
        case 2:
            editCompany();
            break;
        case 3:
            // Call the function for generating reports (not implemented yet)
            openReportsMenu();
            break;
        case 4:
            registerUser();
            break;
        case 5:
            printf("Saindo do sistema. Até logo!\n");
            return; // Sair do programa
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    }
}

void openReportsMenu()
{
    int option;
    while (1)
    {
        printf("\n--- Menu de Relatórios ---\n");
        printf("1 - Relatório por Empresa\n");
        printf("2 - Relatórios Globais\n");
        printf("3 - Retornar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            reportByCompany();
            break;
        case 2:
            // globalReports();
            break;
        case 3:
            printf("Retornando ao menu principal...\n");
            return;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    }
}

void registerCompany()
{
    FILE *file = openFile(COMPANY_FILE, "a");
    if (!file)
    {
        return;
    }

    char name[MAX_LENGTH], cnpj[MAX_LENGTH], tel[MAX_LENGTH], email[MAX_LENGTH], rua[MAX_LENGTH],
        bairro[MAX_LENGTH], cidade[MAX_LENGTH], estado[MAX_LENGTH], cep[MAX_LENGTH];

    getInput("\nCadastro de Nova Empresa\nNome da empresa: ", name, MAX_LENGTH);
    getInput("CNPJ: ", cnpj, MAX_LENGTH);
    getInput("Telefone: ", tel, MAX_LENGTH);
    getInput("Rua: ", rua, MAX_LENGTH);
    getInput("Bairro: ", bairro, MAX_LENGTH);
    getInput("Cidade: ", cidade, MAX_LENGTH);
    getInput("Estado: ", estado, MAX_LENGTH);
    getInput("CEP: ", cep, MAX_LENGTH);
    getInput("Email: ", email, MAX_LENGTH);

    fprintf(file, "Nome: %s, CNPJ: %s, Telefone: %s, Endereço: %s, Bairro: %s, Cidade: %s, Estado: %s, CEP: %s, Email: %s\n",
            name, cnpj, tel, rua, bairro, cidade, estado, cep, email);
    fprintf(file, "###END_COMPANY###\n"); // Add company separator
    closeFile(file);
    printf("Empresa cadastrada com sucesso!\n");
}

void registerUser()
{
    FILE *file = openFile(USER_FILE, "a");
    if (!file)
    {
        return;
    }

    char username[MAX_LENGTH], password[MAX_LENGTH];
    getInput("\nCadastro de Novo Usuário\nNome de usuário: ", username, MAX_LENGTH);
    getInput("Senha: ", password, MAX_LENGTH);

    fprintf(file, "%s %s\n", username, password);
    closeFile(file);
    printf("Usuário cadastrado com sucesso!\n");
}

void editCompany()
{
    int option;
    char companyNames[100][MAX_LENGTH];
    int companyCount = 0;

    while (1)
    {
        listCompanies(companyNames, &companyCount);
        if (companyCount == 0)
        {
            printf("Nenhuma empresa encontrada.\n");
            return;
        }

        option = selectCompany(companyCount);
        if (option == 0)
        {
            printf("Retornando ao menu principal...\n");
            return;
        }

        char targetCompany[MAX_LENGTH];
        strncpy(targetCompany, companyNames[option - 1], MAX_LENGTH);
        targetCompany[MAX_LENGTH - 1] = '\0';

        printf("\nVocê escolheu: %s\n", targetCompany);

        FILE *file = openFile(COMPANY_FILE, "r");
        if (!file)
        {
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (!tempFile)
        {
            printf("Erro: Não foi possível criar o arquivo temporário.\n");
            fclose(file);
            return;
        }

        bool companyFound = processCompanyEdit(file, tempFile, targetCompany);

        fclose(file);
        fclose(tempFile);

        if (companyFound)
        {
            remove(COMPANY_FILE);
            rename("temp.txt", COMPANY_FILE);
        }
        else
        {
            remove("temp.txt");
            printf("Empresa '%s' não encontrada.\n", targetCompany);
        }
    }
}

void listCompanies(char companyNames[][MAX_LENGTH], int *companyCount)
{
    FILE *file = openFile(COMPANY_FILE, "r");
    if (!file)
    {
        return;
    }

    char companyLine[MAX_LENGTH];
    *companyCount = 0;
    printf("\n--- Empresas registradas ---\n");
    while (fgets(companyLine, MAX_LENGTH, file))
    {
        if (strstr(companyLine, "Nome:"))
        {
            char *start = strstr(companyLine, "Nome:") + 6;
            char *end = strchr(start, ',');
            if (end)
                *end = '\0';
            strncpy(companyNames[*companyCount], start, MAX_LENGTH);
            printf("%d - %s\n", *companyCount + 1, start);
            (*companyCount)++;
        }
    }
    fclose(file);
}
int selectCompany(int companyCount)
{
    int option;
    printf("\nEscolha o número da empresa que deseja editar ou digite 0 para retornar ao menu principal: ");
    scanf("%d", &option);
    if (option < 0 || option > companyCount)
    {
        printf("Escolha inválida.\n");
        return selectCompany(companyCount);
    }
    return option;
}

void addMonthlyInfo(FILE *file, FILE *tempFile, const char *targetCompany)
{
    char buffer[MAX_LENGTH];
    bool insideTargetCompany = false;

    while (fgets(buffer, MAX_LENGTH, file))
    {
        // Verificar se a linha marca o começo de uma nova empresa
        if (strncmp(buffer, "Nome:", 5) == 0)
        {
            insideTargetCompany = strstr(buffer, targetCompany) != NULL;
        }

        // Verificar se estamos entre uma empresa e o a linha que sinalizar o fim de uma empresa
        if (insideTargetCompany && strcmp(buffer, "###END_COMPANY###\n") == 0)
        {
            char month[MAX_LENGTH];
            double wasteTreatment, cost;

            printf("Digite o mês (ex: Novembro): ");
            scanf(" %[^\n]", month);
            printf("Digite a quantidade de lixo tratado (em toneladas): ");
            scanf("%lf", &wasteTreatment);
            printf("Digite o custo estimado (em reais): ");
            scanf("%lf", &cost);

            // Adiciona as informações dos meses antes da linha ###END_COMPANY###
            fprintf(tempFile, "  - Mês: %s, Tratamento: %.2f toneladas, Custo: %.2f reais\n",
                    month, wasteTreatment, cost);

            printf("Informações mensais adicionadas com sucesso!\n");
        }

        fprintf(tempFile, "%s", buffer);
    }
}

bool processCompanyEdit(FILE *file, FILE *tempFile, const char *targetCompany)
{
    char buffer[MAX_LENGTH];
    bool companyFound = false;
    bool insideTargetCompany = false;

    while (fgets(buffer, MAX_LENGTH, file))
    {
        if (strncmp(buffer, "Nome:", 5) == 0)
        {
            if (insideTargetCompany)
            {
                fprintf(tempFile, "\n");
            }
            insideTargetCompany = strstr(buffer, targetCompany) != NULL;
        }

        // Write the current line to temp file
        fprintf(tempFile, "%s", buffer);

        if (insideTargetCompany && !companyFound)
        {
            companyFound = true;
            printf("\nEmpresa encontrada: %s\n", buffer);
            int subOption;
            printf("Escolha uma opção:\n");
            printf("1 - Atualizar informações gerais\n");
            printf("2 - Adicionar informações mensais (Tratamento de Lixo e Custo)\n");
            printf("3 - Retornar ao menu principal\n");
            printf("Escolha uma opção: ");
            scanf("%d", &subOption);

            if (subOption == 1)
            {
                updateCompanyInfo(tempFile);
            }
            else if (subOption == 2)
            {
                addMonthlyInfo(file, tempFile, targetCompany);
            }
            else if (subOption == 3)
            {
                printf("Retornando ao menu principal...\n");
                return false;
            }
        }
    }
    return companyFound;
}

void updateCompanyInfo(FILE *tempFile)
{
    char updatedLine[MAX_LENGTH];
    while (getchar() != '\n')
        ;

    printf("Digite as novas informações para a empresa:\n");
    printf("Exemplo: Nome: Empresa A, Endereço: Rua XYZ\n");
    fgets(updatedLine, MAX_LENGTH, stdin);
    updatedLine[strcspn(updatedLine, "\n")] = 0; // Remove newline

    fprintf(tempFile, "%s\n", updatedLine);
}

int loadCompanies(const char *filename, Company companies[], int maxCompanies)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int count = 0;
    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file) && count < maxCompanies)
    {
        // Start parsing a new company
        if (strncmp(line, "Nome:", 5) == 0)
        {
            sscanf(line, " Nome: %99[^,], CNPJ: %19[^,], Telefone: %19[^,], Endereço: %199[^,], Bairro: %199[^,], Cidade: %199[^,], Estado: %2[^,], CEP: %9[^,], Email: %99[^\n]",
                   companies[count].nome,
                   companies[count].cnpj,
                   companies[count].telefone,
                   companies[count].rua,
                   companies[count].bairro,
                   companies[count].cidade,
                   companies[count].estado,
                   companies[count].cep,
                   companies[count].email);

            companies[count].numMonths = 0; // Initialize monthly data count

            // Parse monthly data until the end of the company section
            while (fgets(line, sizeof(line), file))
            {
                // Stop if a new company starts or end marker is found
                if (strncmp(line, "###END_COMPANY###", 17) == 0 || strncmp(line, "Nome:", 5) == 0)
                {
                    break;
                }

                // Parse monthly data if line starts with "  -"
                if (strncmp(line, "  -", 3) == 0 && companies[count].numMonths < 12)
                {
                    sscanf(line, "  - Mês: %19[^,], Tratamento: %lf toneladas, Custo: %lf reais",
                           companies[count].month[companies[count].numMonths],
                           &companies[count].wasteTreatment[companies[count].numMonths],
                           &companies[count].cost[companies[count].numMonths]);

                    companies[count].numMonths++;
                }
            }

            count++; // Move to the next company
        }
    }

    fclose(file);
    return count;
}

int reportByCompany()
{
    Company empresas[100]; // Increased array size to handle multiple companies
    int numEmpresas = loadCompanies(COMPANY_FILE, empresas, 100);

    for (int i = 0; i < numEmpresas; i++)
    {
        printf("\nEmpresa: %s\n", empresas[i].nome);
        printf("CNPJ: %s\n", empresas[i].cnpj);
        printf("Telefone: %s\n", empresas[i].telefone);
        printf("\nDados Mensais:\n");
        for (int j = 0; j < empresas[i].numMonths; j++)
        {
            printf("Mês: %s\n", empresas[i].month[j]);
            printf("Tratamento de Lixo: %.2f toneladas\n", empresas[i].wasteTreatment[j]);
            printf("Custo: R$ %.2f\n", empresas[i].cost[j]);
            printf("----------------------------------\n");
        }
    }
    return 0;
}
