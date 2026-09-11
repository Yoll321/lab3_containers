template <typename value_t>
class Node2 {
public:
    Node2(value_t val = value_t())
        : val(val), next(nullptr), prev(nullptr) {}
    value_t val;
    Node2 *next;
    Node2 *prev;
};

template <typename value_t>
class NodeList2 {
public:
    class iterator {
    public:
        iterator(Node2<value_t> *node) : current(node){};

        value_t& operator*() const {
            return current->val;
        }

        iterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    private:
        Node2<value_t> *current;
    };

    NodeList2() : head(nullptr), tail(nullptr), size_val(0) {}

    NodeList2(NodeList2&& other)
        : head(other.head), tail(other.tail), size_val(other.size_val) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_val = 0;
    }

    NodeList2& operator=(NodeList2&& other) {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_val = other.size_val;
        }
        return *this;
    }

    void clear(void) {
        auto current = head;
        while (current) {
            auto next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size_val = 0;
    }

    ~NodeList2() {
        clear();
    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }
    
    void push_back(value_t val) {
        if (size_val == 0) {
            head = new Node2<value_t>(val);
            tail = head;
        } else {
            tail->next = new Node2<value_t>(val);
            tail->next->prev = tail;
            tail = tail->next;
        }
        size_val++;
    }

    value_t erase(unsigned int pos) {
        value_t retval;
        if (pos == 0) {
            auto to_delete = head;
            head = head->next;
            head->prev = nullptr;
            retval = to_delete->val;
            delete to_delete;
        } 
        
        else if (pos == size_val - 1) {
            auto to_delete = tail;
            tail = tail->prev;
            to_delete->prev->next = nullptr;
            delete to_delete;
        }

        else {
            auto to_delete = this->get_node(pos);
            if (!to_delete) return value_t();
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
            delete to_delete;
        }
        size_val--;
        return retval;
    }

    void erase(std::vector<unsigned int> pos_pool) {
        std::sort(pos_pool.begin(), pos_pool.end());
        for (unsigned int i = 0; i < pos_pool.size(); i++) {
            pos_pool[i] -= i;
        }

        for (auto pos : pos_pool) {
            this->erase(pos);
        }
        return;
    }

    void insert(value_t val, unsigned int pos) {
        auto new_node = new Node2<value_t>(val);
        if (pos == 0) {
            new_node->next = this->head;
            this->head->prev = new_node;
            this->head = new_node;
        } else if (pos == size_val) {
            this->push_back(val);
        } else {
            auto prev = get_node(pos - 1);
            if (!prev) return;
            new_node->prev = prev;
            new_node->next = prev->next;
            prev->next->prev = new_node;
            prev->next = new_node;
        }
        size_val++;
        return;
    }

    unsigned int size(void) {
        return this->size_val;
    }

private:
    unsigned int volume;
    unsigned int size_val;
    Node2<value_t> *head;
    Node2<value_t> *tail;

    Node2<value_t> *get_node(unsigned int pos) {
        if (pos >= size_val) {
            throw std::out_of_range("Index out of range");
            return nullptr;
        }
        
        Node2<value_t> *retval = head;
        for (unsigned int i = 1; i <= pos; i++) {
            retval = retval->next;
        }
        return retval;
    }
};