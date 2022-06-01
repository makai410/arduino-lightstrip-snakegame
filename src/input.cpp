int get_direction()
{
    int x = analogRead(A0);
    //读取A1值并发送
    int y = analogRead(A1);

    if (x < 250)
    {
        return 1;
    }

    if (x > 750)
    {
        return 3;
    }

    if (y < 250)
    {
        return 2;
    }

    if (y > 750)
    {
        return 0;
    }

    return -1;
}