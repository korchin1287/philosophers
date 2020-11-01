static int          ft_strlen(char *str)
{
    int             len;
    len = 0;
    while (str && str[len])
        len++;
    return (len);
}
static void         put_message(char *msg, char **ptr)
{
    while (*msg)
        *(*ptr)++ = *msg++;
}
static void         put_number(size_t nbr, char **ptr)
{
    char            c;
    size_t          nbr_tmp;
    long long       pow;
    pow = 10;
    nbr_tmp = nbr;
    while (nbr_tmp /= 10)
        pow *= 10;
    while ((pow /= 10))
    {
        c = (nbr / pow) % 10 + 48;
        *(*ptr)++ = c;
    }
}
void                ft_putstr(const char *str)
{
    char        *ptr;
    ptr = (char *)str;
    while (ptr && *ptr)
        write(STD_OUT, ptr++, 1);
}
int                 print_status(t_philosopher *phil, struct timeval tv, \
                                                            char *msg)
{
    char            *ptr;
    char            *log;
    size_t          size_n;
    long long       tmp;
    long long       time;
    tmp = phil->index * 10;
    size_n = 4 + ft_strlen(msg);
    while (tmp /= 10)
        size_n++;
    time = ((tv.tv_sec - phil->params->s_time.tv_sec) * 1000
            + (tv.tv_usec - phil->params->s_time.tv_usec) * 0.001);
    tmp = time;
    while (tmp /= 10)
        size_n++;
    if (!(log = malloc(sizeof(char) * (size_n))))
        return (MALLOC);
    ptr = log;
    put_number((size_t)time, &ptr);
    put_message("ms ", &ptr);
    put_number(phil->index, &ptr);
    put_message(msg, &ptr);
    write(1, log, size_n);
    free(log);
    return (SUCCESS);
}