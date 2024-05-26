
// Teht 14, 15

#include <iostream>
#include <cstring>  
#include <cstdlib>  
#include <utility>  

class Big_Data {
public:
    // Konstruktori
    explicit Big_Data(size_t size)
        : size_(size), data_(static_cast<char*>(std::malloc(size))) {
        if (!data_) {
            throw std::bad_alloc();
        }
    }

    // Kopiokonstruktori
    Big_Data(const Big_Data& other)
        : size_(other.size_), data_(static_cast<char*>(std::malloc(other.size_))) {
        if (!data_) {
            throw std::bad_alloc();
        }
        std::memcpy(data_, other.data_, other.size_);
    }

    // Sijoitusoperaattori
    Big_Data& operator=(const Big_Data& other) {
        if (this != &other) {
            // Vapautetaan nykyinen bufferi
            std::free(data_);
            size_ = other.size_;
            data_ = static_cast<char*>(std::malloc(other.size_));
            if (!data_) {
                throw std::bad_alloc();
            }
            std::memcpy(data_, other.data_, other.size_);
        }
        return *this;
    }

    // Move-konstruktori
    Big_Data(Big_Data&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    // Move-sijoitusoperaattori
    Big_Data& operator=(Big_Data&& other) noexcept {
        if (this != &other) {
            // Vapautetaan nykyinen bufferi
            std::free(data_);
            // Siirretään resurssit
            size_ = other.size_;
            data_ = other.data_;
            // Nollataan alkuperäinen olio
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    // Destruktori
    ~Big_Data() {
        std::free(data_);
    }


private:
    size_t size_;
    char* data_;
};

// Testiohjelma
int main() {
    try {
        // Testataan move-konstruktoria
        Big_Data a(Big_Data(1024));
        std::cout << "a.data(): " << static_cast<void*>(a.data()) << std::endl;

        // Testataan move-sijoitusoperaattoria
        Big_Data b(1024);
        b = Big_Data(1024);
        std::cout << "b.data(): " << static_cast<void*>(b.data()) << std::endl;

        // Testataan move-sijoitusoperaattoria std::move:lla
        Big_Data c(std::move(a));
        std::cout << "c.data(): " << static_cast<void*>(c.data()) << std::endl;
        std::cout << "a.data() after move: " << static_cast<void*>(a.data()) << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    }

    return 0;
}

// Teht 16  

int main() {
    std::vector<void*> allocations;
    try {
        while (true) {
            // Yritetään varata muistia paljon
            void* ptr = new char[1024 * 1024 * 10]; 
            allocations.push_back(ptr);
            std::cout << "10mb allocated,totaL: " << allocations.size() << std::endl;
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "memory allocation faIL: " << e.what() << std::endl;
    }

// Ohjelma ottaa kiinni std::bad_alloc-poikkeuksen ja tulostaa viestin epäonnistuneesta muistinvarauksesta. Ohjelma varaa muistia toistuvasti, kunnes järjestelmä ei enää kykene allokoimaan tarvittavaa määrää. muistinvarauksen epäonnistumiseen tulisi varautua ohjelmoitaessa.


// Teht 17

// Poikkeuksia kannattaa käyttää koska ne mahdollistaa virheiden käsittelyn keskitetysti. Catch lohko voi käsitellä monia poikkeuksia joka tekee koodista vähemmän toisteista. Poikkeusten käyttö mahdollistaa myös virheenkäsittelyn erottamisen ohjelman normaalista toiminnasta. Syitä miksi ei käyttää on esimerkiksi suorituskyvyn lasku ja poikkeukset voivat myös tehdä ohjelmasta monimutkaisemman ja vaikeampi lukuisen varsinkin jos poikkeuksia on paljon.