#include<bits/stdc++.h>
using namespace std;
struct node{
    public:
        char id;//char para identificar el nodo
        int h;// un entero para la heuristica
        int exp;//un entero para saber cuantas veces fue expandido el nodo
        bool vis;//un bool para saber si fue visitado
        node(char id, int h){
            this->id=id;//iniciamos los valores
            this->h=h;
            exp=0;
            vis=false;
            exp=0;
        }
        void reset(){
            exp=0;
            vis=false;
        }
        
};

struct arista{
    public:
    char src;//nodo fuente
    char dest;//nodo destino
    int peso;//costo de la arista
    arista(char src, char dest, int peso){
        this->src = src;//iniciamos los valores
        this->dest = dest;
        this->peso = peso;
    }
};
void insert(vector<pair<string,int>> &v, pair<string, int> p){
    
    /*
        Esta es una funcion para insertar valores al principio del vector pq en la funcion de busqueda de costo uniforme
        de modo tal que quede ordenado por costo acumulado
    */
    int pos=0;//la posicion del elemento dentro del vector
    v.resize(v.size()+1);//aumentamos en uno el tamaño antes de insertar 
    if(v.size()==1){//si el vector despues del resize tiene tamaño 1, implica que es el primer elemento a ser insertado por lo que se inserta de una vez
        v[0]=p;
    }else{//si no, se loopea hasta encontrar un valor mayor o igual al valor a insertar
        for(int i=0;i<v.size();i++){
            if(v[i].second>=p.second){
                pos=i;//cuando se encuentra, se inicia otro ciclo para mover todos los demás elementos 1 posicion a la derecha
                for(int j=v.size()-1; j>pos;j--){
                    v[j]=v[j-1];
                }
                v[pos]=p;//e insertamos el nuevo valor en el espacio en el que va 
                break;
            }
            if(i==v.size()-1){
                v[i]=p;//en caso de no encontrar ningun valor mayor, se inserta al final
            }                
        }
    }
}

struct fdx{
    public://estructura para A-Star
    string s;//string para simbolizar el camino
    int h;// entero para la heuristica
    int costoAcumulado;// entero para el costo acumulado
    fdx(){
        //constructor vacio para poder crear un fdx sin parametros
    };
    fdx(string s, int h, int costoAcumulado){//constructor con parametros para setear los valores 
        this->s=s;
        this->h=h;
        this->costoAcumulado=costoAcumulado;
        
    }
    int getFdx(){//funcion que entrega la suma de la heurisitica y el costo acumulado para obtener f(x)
        return h+costoAcumulado;
    }
};
void insertAStar(vector<fdx> &v, fdx f){
    /*
    
        similar a la funcion de insertar pero para A-Star, esta ordena por f(x) en lugar de costo acumulado

    */
    int pos=0;
    v.resize(v.size()+1);
    if(v.size()==1){
        v[0]=f;
    }else{
        for(int i=0;i<v.size();i++){
            if(v[i].getFdx()>=f.getFdx()){
                pos=i;
                for(int j=v.size()-1; j>pos;j--){
                    v[j]=v[j-1];
                }
                v[pos]=f;
                break;
            }
            if(i==v.size()-1){
                v[i]=f;
            }                
            }
        }
}
struct graph{
    public://struct para el grafo completo
        vector<node> g;//vector de nodos
        map<char, vector<arista>> l;//vector de aristas
        graph(int n){
            //constructor vacio
        }
        void pushNode(node n){
            g.push_back(n);//funcion para insertar un nodo en la lista de nodos
        }
        void pushArista(arista a){
            l[a.src].push_back(a);//funcion para insertar una arista en la lista de aristas
        }
        /*
            Funciones para depurar
        */
        void printNodes(){
            cout<<"Imprimiendo Nodos: "<<endl;
            for(auto it: g){
                cout<<"nodo: "<< it.id<<" heuristica: "<<it.h<<endl;
            }
        }
        void printAristas(){
            cout<<"Imprimiendo Aristas: "<<endl;
            for(auto it: l){
                cout<<"aristas del nodo "<<it.first<<": "<<endl;
                for(auto i: it.second){
                    cout<<" nodo destino: "<<i.dest<<" peso: "<< i.peso<<endl;
                }
                
            }
        }
        /*
            funcion que reinicia la cantidad de veces que los nodos se expandieron y si fueron visitados
        */
        void limpiar(){
            for(int i=0; i<g.size();i++){
                g[i].reset();
            }
        }
        /*
            funcion que imprime la cantidad de veces que un nodo fue expandido
        */
        void printExpansion(){
            for(auto i: g){
                cout<<i.id<<": "<<i.exp<<endl;
            }
        }
        /*
            1ra funcion de las solicitadas, dfs, recorre el grafo seleccionando como siguiente nodo, algun hijo del nodo actual de manera aleatoria
            se detiene cuando el nodo actual sea el nodo destino
        */
        void dfs(char ini, char dest){
            limpiar();//llamamos a la funcion limpiar para reiniciar el estado del grafo
            vector<char> camino;//creamos un vector para guardar el camino
            int costo=0;// y un entero para guardar el costo
            char pos=ini;//la posicion inicial sera el caracter de inicio
            int expaux=search(ini);//creamos una variable auxiliar para aumentar la variable que simboliza la expansion de primer nodo
            g[expaux].exp++;//y la aumentamos
            camino.push_back(pos);//ingresamos el nodo inicial al vector del camino
            while(pos!=dest){//loopeamos hasta llegar al destino
                int index= rand()%l[pos].size();//seleccionamos un nodo al azar entre los hijos
                int aux = search(l[pos][index].dest);//buscamos su posicion en el vector de nodos
                if(!g[aux].vis){// revisamos que no haya sido visitado antes
                    costo+=l[pos][index].peso;//aumentamos el costo en base al costo de llegar a ese nodo 
                    pos=g[aux].id;//nos movemos al el nodo seleccionado
                    g[aux].vis=true;//el cual ahora cuenta como visitado
                    g[aux].exp++;//y expandido
                    camino.push_back(pos);//y lo añadimos al vector de camino
                    
                }
            }
            /*
                Imprimimos la salida
            */
            for(int i=0;i<camino.size();i++){
                cout<<camino[i];
                if(i!=camino.size()-1){
                    cout<<"->";
                }
            }
            cout<<endl;
            cout<<"Costo: "<<costo<<endl;
            if(costo==18){
                cout<<"Es óptima"<<endl;
            }else{
                cout<<"No es óptima"<<endl;
            }
            printExpansion();

        }

        /*
            2da Funcion solicitada, esta recorre el grafo llendose por el nodo hijo del nodo actual con menor heuristica 
        */
        void greedy(char ini, char dest){
            limpiar();//llamamos a la funcion limpiar para reiniciar el estado del grafo
            vector<char> camino;//definimos vector para el camino
            char pos=ini;//entero para el nodo actual
            int costo=0;// y un entero para guardar el costo
            int expaux=search(ini);//creamos una variable auxiliar para aumentar la variable que simboliza la expansion de primer nodo
            g[expaux].exp++;//y la aumentamos
            camino.push_back(pos);//ingresamos el nodo inicial al camino
            while(pos!=dest){//loopeamos hasta que el nodo actual sea el de destino
                int min=INT_MAX;//definimos el minimo como INT_MAX para que el primer valor lo reemplace
                int min_id;//min_id para asociarlo al id de un nodo
                int min_i;//min_i para saber que hijo del nodo actual fue seleccionado y asi saber el costo de moverse a ese nodo 
                int pos_min;// y pos_min para guardar la posicion del menor en el vector de nodos para aumentar el contador de las veces que se expandio
                for(int i=0; i<l[pos].size();i++){//loopeamos por los hijos del nodo actual
                    int aux = search(l[pos][i].dest);//buscamos su posicion en el vector de nodos
                    if(g[aux].h<min){//si la heuristica del nodo es menor que el valor min almacenado actualmente
                        min_id=g[aux].id;//actualizamos el id
                        min=g[aux].h;//el valor del minimo
                        min_i=i;//el valor actual de i
                        pos_min=aux;//y el valor de su posicion
                    }
                }
                costo+=l[pos][min_i].peso;//aumentamos el costo en base al costo de moverse al nodo seleccionado
                g[pos_min].exp++;//aumentamos las veces que se expandio el nodo seleccionado
                pos=min_id;//nos movemos a el
                camino.push_back(pos);//y lo ingresamos al vector de camino
            }
            /*
                Imprimimos la salida
            */
            for(int i=0;i<camino.size();i++){
                cout<<camino[i];
                if(i!=camino.size()-1){
                    cout<<"->";
                }
            }
            cout<<endl;
            cout<<"Costo: "<<costo<<endl;
            if(costo==18){
                cout<<"Es óptima"<<endl;
            }else{
                cout<<"No es óptima"<<endl;
            }
            printExpansion();
        }
        /*
            3ra funcion pedida, busqueda de costo uniforme, esta se va por el nodo con menor costo tomando en cuenta el costo acumulado de llegar a el
        */
        void ucs(char ini, char dest){
            limpiar();//llamamos a la funcion limpiar para reiniciar el estado del grafo
            vector<pair<string,int>> pq;//vector que actuara como cola de prioridad
            string s{ini};//creamos un string con el nodo inicial
            pair<string, int> p(s,0);//creamos un par con el string creado y 0 pues el costo acumulado al inicio es 0
            insert(pq, p);//lo insertamos en el vector
            while(true){//loopeamos infinitamente hasta que se llegue al nodo destino
                string str=pq[0].first;//extraemos el string del primer elemento del vector (esta ordenado gracias al insert)
                char c = str[str.size()-1];//extraemos el ultimo caracter del string, este sera el nodo actual
                if(c==dest){//si ese nodo coincide con el de destino
                    break;//rompemos el ciclo
                }
                int costo=pq[0].second;//el costo actual es el costo guardado en el 2do valor del pair en el vector
                int pos= search(c);//buscamos la posicion del nodo actual en el vector de nodos del grafo
                g[pos].vis=true;//lo maracamos como visitado
                g[pos].exp++;//aumentamos las veces que fue visitado
                pq.erase(pq.begin());// lo sacamos del vector
                for(int i=0; i<l[c].size();i++){//loopeamos por sus hijos
                    int aux2 = search(l[c][i].dest);//buscamos la posicion de su hijo actual en el vector de nodos del grafo
                    string camino = str + g[aux2].id;//añadimos ese caracter al string 
                    int costoAcumulado = costo + l[c][i].peso;//añadimos el costo de llegar a el al costo acumulado
                    pair<string, int> in(camino, costoAcumulado);//creamos el par
                    insert(pq, in);//y lo insertamos en el vector
                }   
            }
            /*
                Imprimimos la salida 
            */
            for(int i=0;i<pq[0].first.size();i++){
                cout<<pq[0].first[i];
                if(i!=pq[0].first.size()-1){
                    cout<<"->";
                }
            }
            cout<<endl;
            cout<<"Costo: "<<pq[0].second<<endl;
            if(pq[0].second==18){
                cout<<"Es óptima"<<endl;
            }else{
                cout<<"No es óptima"<<endl;
            }
            printExpansion();
        }
        /*
            4ta funcion solicitada, A-Star, similar a UCS pero usa tambien la heuristica, resultando en que elige un nodo basado en la suma de 
            la heuristica y el costo acumulado, seleccionando el de menor valor
        */
        void aStar(char ini, char dest){
            limpiar();//llamamos a la funcion limpiar para reiniciar el estado del grafo
            vector<fdx> pq;//vector que actuara como cola de prioridad
            int auxini= search(ini);//buscamos la posicion del nodo inicial en el vector de nodos del grafo
            string s{ini};//creamos un string con su id
            fdx f(s,g[auxini].h, 0);//y creamos una instancia de fdx con la id del nodo, la heuristica del nodo y 0 pues aun no hay costo acumulado 
            insertAStar(pq, f);//lo insertamos con la funcion de insercion creada anteriormente
            while(true){//iteramos hasta que se llegue al break
                
                string str=pq[0].s;//extraemos el string del primer elemento del vector (esta ordenado gracias al insert)
                char c = str[str.size()-1];//extraemos el ultimo caracter del string, este sera el nodo actual
                if(c==dest){//si ese nodo coincide con el de destino
                    break;//rompemos el ciclo
                }
                int costo=pq[0].costoAcumulado;//el costo actual es el costo acumulado hasta el nodo
                int pos= search(c);//buscamos la posicion del nodo actual en el vector de nodos del grafo
                g[pos].vis=true;//lo maracamos como visitado
                g[pos].exp++;//aumentamos las veces que fue visitado
                pq.erase(pq.begin());// lo sacamos del vector
                for(int i=0; i<l[c].size();i++){//loopeamos por sus hijos
                    int aux2 = search(l[c][i].dest);//buscamos la posicion de su hijo actual en el vector de nodos del grafo
                    string camino = str + g[aux2].id;//añadimos ese caracter al string 
                    int costoAcumulado = costo + l[c][i].peso;//añadimos el costo de llegar a el al costo acumulado
                    fdx faux(camino, g[aux2].h, costoAcumulado);//creamos una instancia de fdx con el camino actual, la heuristica del nodo seleccionado y el costo acumulado hasta ese nodo
                    insertAStar(pq, faux);//lo insertamos en el vector
                }   
            }
            /*
                imprimimos la salida
            */
            for(int i=0;i<pq[0].s.size();i++){
                cout<<pq[0].s[i];
                if(i!=pq[0].s.size()-1){
                    cout<<"->";
                }
            }
            cout<<endl;
            cout<<"Costo: "<<pq[0].costoAcumulado<<endl;
            if(pq[0].costoAcumulado==18){
                cout<<"Es óptima"<<endl;
            }else{
                cout<<"No es óptima"<<endl;
            }
            printExpansion();
        }
        /*
            funcion que busca dado un char, la posicion de ese nodo en el vector de nodos
        */
        int search(char c){
            for(int i=0; i<g.size();i++){
                if(g[i].id==c){
                    return i;
                }
            }
            return -1;
        }


};

int main(){
    srand (time(NULL));//seed para el random de dfs
    string ini, dest; //strings para el nodo de inicio y final
    graph g(1);//creamos el grafo
    int cont=0;//contador para el parser
    /*
        Inicio del Parser
    */
    ifstream f("graph.txt");
    string s;
    getline(f,s);
    stringstream ss(s);
    ss>>ini;
    ss>>ini;
    getline(f,s);
    stringstream ss2(s);
    ss2>>dest;
    ss2>>dest;
    map<int,vector<string>> input;
    vector<pair<string, int>> tv;
    
    while(getline(f, s)){
        string aux;
        stringstream ss3(s);
        
        while(ss3>>aux){
            input[cont];
            input[cont].push_back(aux);
            
        }
        cont++;
    }
    int j=1;
    for(int i=0;i<input.size(); i++){
        if(input[i].size()==2){
            node naux(input[i][0][0], stoi(input[i][1]));
            g.pushNode(naux);
        }
        if(input[i].size()==3){
            arista a(input[i][0][0], input[i][1][0], stoi(input[i][2]));
            g.pushArista(a);
        }
    }
    /*
        Fin del Parser
    */

    cout<<"Usando funcion DFS: "<<endl;
    g.dfs(ini[0], dest[0]);
    cout<<endl;
    cout<<"Usando funcion greedy: "<<endl;
    g.greedy(ini[0], dest[0]);
    cout<<endl;
    cout<<"Usando funcion UCS: "<<endl;
    g.ucs(ini[0], dest[0]);
    cout<<endl;
    cout<<"Usando funcion A-Star: "<<endl;
    g.limpiar();
    g.aStar(ini[0],dest[0]);
    return 0;   
}