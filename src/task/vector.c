typedef struct {
    size_t size;
    int *data;
    int total;
} vector;

vector *init_vector(size_t n) 
{
    vector *p = malloc(sizeof(vector));
    if(p) {
        p->data = malloc(n * sizeof(int));
        p->size = n;
        p->total = 0;
    }
    return p;
}

void destroy_vector(vector *v) {
    if(v) {
        free(v->data);
        free(v);
    }
}

size_t resize_vector(vector *v, size_t n) {
    if(v) {
        int *p = realloc(v->data, n * sizeof(int));
        if(p) {
            v->data = p;
            v->size = n;
        }
        return v->size;
    }
    return 0;
}

int vector_get(vector *v, size_t n) {
    if(v && n < v->size) {
        return v->data[n];
    }
    return -1;
}

void set_vector(vector *v, size_t n, int x) {
    if(v) {
        if(n >= v->size) {
            resize_vector(v, n);
        }
        v->data[n] = x;
        v->total++;
    }
}

void push_back(vector *v, int x)
{
    if (v != NULL) 
    {
        set_vector(v, v->size - 1, x);
        v->size++;
    }
}