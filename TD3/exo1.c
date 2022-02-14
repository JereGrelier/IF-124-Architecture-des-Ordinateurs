long f (long i, long j) {
    return (i + j);
}
long a;
void main1 () {
    a = f (1, 2);
    halt();
}
void main2 () {
    a = f (1, 2) + f (3, 4);
    halt();
}
void main3 () {
    a = f (1, f (1, 2));
    halt();
}
