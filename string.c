#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s2: the second string
 * @s3: the first string
 * Return: negative if s3 < s2, positive if s3 > s2, zero if s3 == s2
 */
int _strcmp(char *s3, char *s2)
{
	while (*s3 && *s2)
	{
		if (*s3 != *s2)
			return (*s3 - *s2);
		s3++;
		s2++;
	}
	if (*s3 == *s2)
		return (0);
	else
		return (*s3 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @needle: the substring to find
 * @haystack: string to search
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @src: the source buffer
 * @dest: the destination buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
