#include "../models/DrinksList.hpp"


//construtor vazio;
DrinksList::DrinksList(){}

void  DrinksList::addProduto(Product  newProduct){
    // verificar se já existe produto como código cadastrado, false significa que não existe;
    if (!constainsBarCode(newProduct.getBarCode())){
        // vou cadastrar o produto dinamicamente
        Product*  product = new Product(newProduct);// produto criado dinamicamente

        // atualizar o head
        if (this->size >= this->lenght){
           
        }else{
            // realoca o espaço da lista
        }

        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Produto cadastrado com sucesso!"<<endl; 
        cout<<"---------------------------------------------------------\n"<<endl;
    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Código já cadastrado. Por favor, informe outro código!"<<endl;
        cout<<"---------------------------------------------------------\n"<<endl;
    }
   
}

/* 
void ProductsList::updateProduct(Product* updateproduto, string newDescription, double newPrice){
    //validar dados
    if (newDescription=="" && newPrice <= 0){
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Nenhuma alteração efetuada!"<<endl;
        cout<<"---------------------------------------------------------\n"<<endl;
    }else{
        if (newDescription!=""){
            updateproduto->setDescription(newDescription);
        }
        if (newPrice > 0){
            updateproduto->setUnitPrice(newPrice);
        }
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Produto [" << updateproduto->getBarCode() << "] atualizado com sucesso!"<<endl;
        cout<<"---------------------------------------------------------\n"<<endl;
    }
    
}

void  ProductsList::removeProduct(int barCode){
    
    if (barCode > 0){
        // no inicio da lista
        Product * aux = getHeadProduct();// posição atual
        Product * auxPrevious = getHeadProduct(); // posição anterior
    
        // verifica se vai remover o primeiro produto da lista;    
        if (aux->getBarCode() == barCode ){
            setHeadProduct(aux->getNext());
        
        // Passa para os proximos caso não seja o primeiro da lista;
        }else{
            // atualiza pra o proximo nó com o produto;
            aux = aux->getNext();

            while (aux != nullptr)
            {
                if (aux->getBarCode() == barCode){  
                    break;
                }
                auxPrevious=aux;
                aux = aux->getNext();
            }
        }
        // se o auxiliar for diferente de nulo significa que ele encontrou o produto, senão ele percorreu todos os produto e não encontrou nada;
        if (aux!=nullptr){
            auxPrevious->setNext(aux->getNext());
            delete aux;

            cout<<"\n---------------------------------------------------------"<<endl;
            cout<<"produto de codigo ["<< barCode <<"] deletado com sucesso!"<<endl;
            cout<<"---------------------------------------------------------\n"<<endl;
        }else{
            cout<<"\n---------------------------------------------------------"<<endl;
            cout<<"Codigo ["<< barCode<<"] inexistente. Tente novmente!"<<endl;
            cout<<"---------------------------------------------------------\n"<<endl;
        }
        

    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Não existe código com valor negativo. Tente novmente!"<<endl;
        cout<<"---------------------------------------------------------\n"<<endl;
    }
    
}


bool ProductsList::constainsBarCode(int codigoProduto){
    Product* aux = getHeadProduct();

    while(aux!= nullptr){
        if (aux->getBarCode() == codigoProduto){
            return true;
            break;
        } 

        aux = aux->getNext();
    }
    
    return false;
}

string ProductsList::toLowerText(string text){
    
   for (char&c : text){
        c = tolower(c);
   }
    
    return text;

 }

void ProductsList::searchProductsName(string partName){
    Product* aux = getHeadProduct();


    if (partName!="" && getHeadProduct()!=nullptr){
        int count = 0;
        cout << "Produtos Filtrados"<< endl;
        cout<<"********************************** "<<endl;
        cout << "Cod:  |  Descricao  |  Valor"<< endl;
        cout<<"----------------------------------"<<endl;

        do{
            // pesquisa se existe a parte do nome na descrição, se existir retorna a posição
            if (aux->getDescription().find(toLowerText(partName))!=string::npos){
                count++;
                aux->show(); // imprimir
                 // pega o endereço do proximo produto;
                cout<<"----------------------------------"<<endl;
                
            }
            aux = aux->getNext();

        }while(aux!=nullptr);

        cout<<"Total: "<< count<<endl;

    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Não existe nenhum produto que contenha o nome "<< partName << ". Tente novmente!"<<endl;       
        cout<<"---------------------------------------------------------\n"<<endl;
    }
    
}

Product* ProductsList::searchProduct(int codigoProduto){

    Product* aux = getHeadProduct();

    do{
        if (aux->getBarCode() == codigoProduto){
            return aux;
            break;
        }
        aux = aux->getNext();
    }while(aux != nullptr);
    
    return nullptr;
}

bool ProductsList::isEmpty(){
    return this->headProduct==nullptr;
}

Product* ProductsList::getHeadProduct(){
    return this->headProduct;
}

void ProductsList::setHeadProduct(Product* nextHeadProduct){
    this->headProduct = nextHeadProduct;
}
 
void ProductsList::showProducts(Product * head){

    if(isEmpty()){
        cout<<"Nenhum produto cadastrado"<<endl;
    }else {
        
        Product* aux = this->headProduct; // cria um ponteiro que aponta para o inicio da lista;

        cout << "Cod:  |  Descricao  |  Valor"<< endl;
        cout<<"----------------------------------"<<endl;

        do{ // verifica se existe outro produto
            aux->show(); // imprimir
            aux = aux->getNext(); // pega o endereço do proximo produto;
            cout<<"----------------------------------"<<endl;
        }while (aux != nullptr);

        cout<<"Total produtos: "<< getNElements()<<"\n";
    }
}

ProductsList::~ProductsList(){
    delete this->headProduct;
} */