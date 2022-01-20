struct node
{
	int	value;
};

int main(void)
{
	node n;

	node		*n1 = &n;
	node const	*n2 = &n;
	node		*const n3 = &n;
	node const	*const n4 = &n;

	n1->value = 1;  // 1.
	n2->value = 2;  // 2.
	n3->value = 3;  // 3.
	n4->value = 4;  // 4.
	n1++;           // 5.
	n2++;           // 6.
	n3++;           // 7.
	n4++;           // 8.
	return 0;
}
