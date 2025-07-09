int	td_len(char **td)
{
	int	len;

	len = 0;
	while(td[len])
	{
		len++;
	}
	return (len);
}
