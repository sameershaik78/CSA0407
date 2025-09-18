#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[10] = "---------";

    // File type
    if (S_ISREG(mode)) perms[0] = '-';
    else if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';
    else if (S_ISCHR(mode)) perms[0] = 'c';
    else if (S_ISBLK(mode)) perms[0] = 'b';
    else if (S_ISFIFO(mode)) perms[0] = 'p';
    else if (S_ISSOCK(mode)) perms[0] = 's';

    // Owner permissions
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';

    // Group permissions
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';

    // Others permissions
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("%s", perms);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    // Print permissions
    print_permissions(fileStat.st_mode);
    printf(" ");

    // Number of links
    printf("%ld ", (long)fileStat.st_nlink);

    // Owner name
    struct passwd *pwd = getpwuid(fileStat.st_uid);
    printf("%s ", (pwd != NULL) ? pwd->pw_name : "UNKNOWN");

    // Group name
    struct group *grp = getgrgid(fileStat.st_gid);
    printf("%s ", (grp != NULL) ? grp->gr_name : "UNKNOWN");

    // File size
    printf("%lld ", (long long)fileStat.st_size);

    // Modification time
    char timebuf[80];
    struct tm *tm = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
    printf("%s ", timebuf);

    // Filename
    printf("%s\n", argv[1]);

    return 0;
}
