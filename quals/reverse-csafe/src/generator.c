for (int i = 0; i < 10000000; i++)
{
    int u = i;
    int c = 0;
    while (u > 0)
    {
        int t = u % 10;
        ddd[c++] = (t) % 2 == 0 ? 'a' + t / 2 : '1' + t - 1;
        u /= 10;
    }
    ddd[c] = '\0';
    printf("%s\n", ddd);
}