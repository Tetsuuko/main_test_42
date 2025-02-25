#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

void	strlen_test(const char *str) {
	char *result = (strlen(str) == ft_strlen(str)) ? "OK" : "KO";
	printf("\"%s\": %s\n", str, result);
}

void	run_strlen_tests(void) {
	printf("***FT_STRLEN TEST***\n\n");
	strlen_test("Hello");
	strlen_test("");
	strlen_test(".");
	strlen_test("Je m'appelle Leo");
	printf("\n****\n");
}

void	strcmp_test(const char *s1, const char *s2) {
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", s1, s2, ft_strcmp(s1, s2));
	printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s2, strcmp(s1, s2));
}

void	run_strcmp_test() {
	printf("***FT_STRCMP TEST***\n\n");
	char	s1[2];
	char	s2[2];
	s1[0] = -128;
	s2[0] = -128;
	s1[1] = 0;
	s2[1] = 0;
	strcmp_test(s1, s2);
	strcmp_test("a", "b");
	strcmp_test("b", "a");
	strcmp_test("a", "a");
	strcmp_test("", "a");
	strcmp_test("a", "");
	strcmp_test("01234", "01234");
	strcmp_test("012345", "01234");
	strcmp_test("0\0oui", "0\0non");
	printf("\n****\n");
}

void	strcpy_test(char *s1, const char *s2) {
	char *alloc_ft_strcpy = strdup(s1);
	char *alloc_strcpy = strdup(s1);
	if (alloc_ft_strcpy == NULL || alloc_strcpy == NULL) {
		free(alloc_ft_strcpy);
		free(alloc_strcpy);
		return ;
	}
	printf("ft_strcpy(\"%s\", \"%s\") = %s\n", s1, s2, ft_strcpy(alloc_ft_strcpy, s2));
	printf("strcpy(\"%s\", \"%s\") = %s\n", s1, s2, strcpy(alloc_strcpy, s2));
	free(alloc_ft_strcpy);
	free(alloc_strcpy);
}

void	run_strcpy_test() {
	printf("***FT_STRCPY TEST***\n\n");
	strcpy_test("a", "b");
	strcpy_test("01234", "4321");
	strcpy_test("43210", "0");
	strcpy_test("", "");
	strcpy_test("salut", "");
	printf("\n****\n");
}

void	write_test(int fd,const void *buf, size_t count) {
	ssize_t ft_write_return = ft_write(fd, buf, count);
	int	errno_save = errno;
	printf("\nft_write(%d, %s, %lu) = %zd\n", fd, (const char *)buf, count, ft_write_return);
	if (ft_write_return < 0) {
		printf("Errno = %d\n", errno_save);
		perror("Error msg = ");
	}
	ssize_t write_return = write(fd, buf, count);
	errno_save = errno;
	printf("\nwrite(%d, %s, %lu) = %zd\n", fd, (const char *)buf, count, write_return);
	if (write_return < 0) {
		printf("Errno = %d\n", errno_save);
		perror("Error msg = ");
	}
}

void	run_write_test() {
	printf("***FT_WRITE TEST***\n\n");
	write_test(1, "", 1);
	write_test(1, "YO", 0);
	write_test(1, "YO", 2);
	write_test(1, "YO", 1);
	write_test(5, "YO", 2);
	write_test(1, "YO", 0);
	write_test(-1, "YO", 2);
	int fd = open("write.txt", O_CREAT | O_RDWR | O_TRUNC, 0755);
	write_test(fd, "HELLO", 2);
	int fd2 = open("bad_write.txt", O_CREAT | O_RDONLY | O_TRUNC, 0755);
	write_test(fd2, "HELLO", 2);
	printf("\n****\n");
	close(fd);
	close(fd2);
}

void	read_test(int fd, void *buf, size_t count) {
	ssize_t read_return = ft_read(fd, buf, count);
	int errno_save = errno;
	printf("\nft_read(%d, %s , %lu) = %zd\n", fd, (char *)buf, count, read_return);
	if (read_return < 0) {
		printf("Errno = %d\n", errno_save);
		perror("Error msg = ");
	}
}

void	run_read_test() {
	printf("***FT_READ TEST***\n\n");
	char	str[50];
	memset(str, 0, 50);
	read_test(0, str, 49);
	int fd = open("read.txt", O_CREAT | O_RDWR | O_TRUNC, 0755);
	write(fd, "bonjour", strlen("bonjour"));
	memset(str, 0, 50);
	close(fd);
	fd = open("read.txt", O_RDWR);
	read_test(fd, str, 49);
	memset(str, 0, 50);
	close(fd);
	fd = open("read.txt", O_RDWR);
	read_test(fd, str, 0);
	close(fd);
	fd = open("bad_read.txt", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	write(fd, "bonjour", strlen("bonjour"));
	memset(str, 0, 50);
	read_test(fd, str, 49);
	close(fd);
	printf("\n****\n");
}

void	strdup_test(const char *str) {
	char	*ft_dup = ft_strdup(str);
	int errno_save = errno;
	if (ft_dup == NULL) {
		printf("ft_strdup of \"%s\" is %p\n", str, ft_dup);
		printf("errno = %d\n", errno_save);
		perror("perror = ");
	}
	else {
		printf("ft_strdup of  \"%s\" = %s\n", str, ft_dup);
	}
	char *dup = strdup(str);
	errno_save = errno;
	if (dup == NULL) {
		printf("strdup of \"%s\" is %p\n", str, dup);
		printf("errno = %d\n", errno_save);
		perror("perror = ");
	}
	else {
		printf("strdup of  \"%s\" = %s\n", str, dup);
	}
	if (dup != NULL && ft_dup != NULL) {
		printf("strcmp(ft_strdup, strdup) = %d\n", strcmp(ft_dup, dup));
	}
	free(ft_dup);
	free(dup);
}

void	malloc_fail_test() {
	int big_len = 50000;
	char big[big_len];
	memset(big, 97, big_len);
	big[big_len - 1 ] = 0;
	strdup_test(big);
}

void	run_strdup_test() {
	printf("***FT_STRDUP TEST***\n\n");
	strdup_test("salut");
	strdup_test("");
	strdup_test("Z");
	// malloc_fail_test();
	printf("\n****\n");
}

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	run_strlen_tests();
	run_strcmp_test();
	run_strcpy_test();
	run_write_test();
	run_read_test();
	run_strdup_test();
	return 0;
}