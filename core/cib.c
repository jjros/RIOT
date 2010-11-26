typedef struct cib {
    unsigned int read_count;
    unsigned int write_count;
    unsigned int complement;
} cib_t;

void cib_init(cib_t *cib, unsigned int size) {
    cib->read_count = 0;
    cib->write_count = 0;
    cib->complement = 0-size;
}

int cib_avail (cib_t *cib) {
    return cib->write_count - cib->read_count;
}

int cib_get(cib_t *cib) {
    int avail = cib_avail (cib);

    if (avail > 0) {
        return cib->read_count++ & ~cib->complement;
    } 

    return -1;
}

int cib_put(cib_t *cib) {
    int avail = cib_avail (cib);

    if ((int)(avail + cib->complement) < 0 ) {
        return cib->write_count++ & ~(cib->complement);
    }

    return -1;
}

/*
int main() {
    cib_t cib;

    cib_init(&cib, 0);

    int res = cib_get(&cib);

    printf("%i\n", res);
}
*/