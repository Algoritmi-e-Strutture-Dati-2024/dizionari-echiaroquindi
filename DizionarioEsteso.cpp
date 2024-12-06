#include <iostream>
#include <string>

template <typename T>
class DizionarioEsteso {
private:
    static const int TABLE_SIZE = 100; // Dimensione fissa della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false;
    };

    Entry table[TABLE_SIZE];

    // Funzione hash di base
    int hashFunction(const std::string key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE; // Algoritmo di hashing semplice
        }
        return hash;
    }

public:
    // Aggiunge una coppia chiave-valore alla tabella hash. Se la posizione calcolata dalla funzione hash è già occupata, segnala una collisione e non gestisce l'inserimento:
    void inserisci(const std::string key, const T value) {
        int index = hashFunction(key);

        if (table[index].isOccupied) {
            std::cerr << "Collision detected for key: " << key << " at index " << index << ". Not handling collisions.\n";
            return;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    // Restituisce il valore associato a una chiave data. Se la chiave non è trovata, ritorna "Key not found!":
    T recupera(const std::string key) const {
        int index = hashFunction(key);

        if (table[index].isOccupied && table[index].key == key) {
            return table[index].value;
        }

        return "Key not found!";
    }

    // verifica se una chiave è presente nel dizionario
    bool appartiene(const std::string key) const {
        int index = hashFunction(key);
        
        // Se esiste e la cella è occupata e il suo valore è esattamente key restituisce la stessa
        return table[index].isOccupied && table[index].key == key;
    }

    //Rimuove una coppia chiave-valore dal dizionario. Se la chiave è trovata e occupata, la rimuove e ritorna true, altrimenti ritorna false:
    bool cancella(const std::string key) {
        int index = hashFunction(key);

        // Se la trova e la cella è occupata e ha lo stesso valore key, quindi sarà uguale a false; la eliminerà
        if (table[index].isOccupied && table[index].key == key) {
            table[index].isOccupied = false;
            return true;
        }

        return false; //restituirà falso se La chiave non esiste
    }

    // stampa del contenuto del dizionario
    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};

#include <iostream>

int main() {
// esempio di DizionarioEsteso
    DizionarioEsteso<int> dizionario;

    dizionario.inserisci("computer", 15);
    dizionario.inserisci("laptop", 25);
    dizionario.inserisci("tablet", 35);
//stampa
    std::cout << "il Contenuto del dizionario è :\n";
    dizionario.stampa();

//collisione
    dizionario.inserisci("pmocuter", 5); // Probabile collisione
    dizionario.inserisci("ltpaop", 10); // Probabile collisione 
    
// dizionario dopo le collisioni
    std::cout << "\nContenuto del dizionario dopo le collisioni:\n";
    dizionario.stampa();

    // valore associato alla chiave "laptop"
    std::cout << "\nValore associato a 'laptop': " << dizionario.recupera("laptop") << "\n";
    std::cout << "Valore associato a 'pmocuter': " << dizionario.recupera("pmocuter") << "\n";

    // Verifica se una chiave esiste
    if (dizionario.appartiene("computer")) {
        std::cout << "'computer' è presente nel dizionario.\n";
    }
    if (!dizionario.appartiene("xilofono")) {
        std::cout << "'xilofono' non è presente nel dizionario.\n";
    }

    // Rimuovi una coppia
    if (dizionario.cancella("laptop")) {
        std::cout << "'laptop' è stato rimosso dal dizionario.\n";
    } else {
        std::cout << "'laptop' non è stato trovato nel dizionario.\n";
    }

    //
    std::cout << "\nContenuto del dizionario dopo la rimozione di 'laptop':\n";
    dizionario.stampa();

    //Tentativo di rimuovere una chiave che non esiste
    if (!dizionario.cancella("okkio")) {
        std::cout << "'okkio' non esiste nel dizionario, impossibile rimuoverlo.\n";
    }

    // Stampa finale del dizionario
    std::cout << "\nStampa il Dizionario:\n";
    dizionario.stampa();

    return 0;
}

