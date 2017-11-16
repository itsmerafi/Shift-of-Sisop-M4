#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/droppledev/Documents";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    char filepath[500];
    int res1308;
    sprintf(filepath,"%s%s",dirpath,path);
    res1308 = lstat(filepath, stbuf);
    if(res1308 == -1){
        return -errno;
    }

    return 0;
}
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi)
{
    char filepath[500];
    if(strcmp(path,"/") == 0){
        path=dirpath;
        sprintf(filepath,"%s",path);
    }
    else sprintf(filepath, "%s%s",dirpath,path);
    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(filepath);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0))
            break;
        }
                                          
        closedir(dp);
        return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi)
{
    (void) fi;
    int fd1308;
    char filepath[500];
    sprintf(filepath,"%s%s",dirpath,path);
    int res1308;
              
    char ekstensii[500];
    int i=0;
    while(i < strlen(filepath) && filepath[i] != '.'){
        i++;
    }
    strcpy(ekstensii, filepath+i);

    char iniperintah[500];
    fd1308 = open(filepath, O_RDONLY);
    if (fd1308 == -1)
        return -errno;
    else{
        if(strcmp(ekstensii, ".pdf") == 0 || strcmp(ekstensii, ".doc") == 0 || strcmp(ekstensii, ".txt") == 0){
            system("zenity --width 450 --error --title 'Error' --text 'Terjadi Kesalahan! File berisi konten berbahaya.'");
            sprintf(iniperintah, "mv %s %s.ditandai && chmod 000 %s.ditandai", filepath, filepath,filepath); //untuk rename
            system(iniperintah);
            return -errno;                                   
        }
              
        res1308 = pread(fd1308, buf, size, offset);
        if (res1308 == -1)
            res1308 = -errno;
            close(fd1308);
        }
        return res1308;
}


static struct fuse_operations xmp_oper = {
  .getattr  = xmp_getattr,
  .readdir  = xmp_readdir,
  .read   = xmp_read,
};

int main(int argc, char *argv[])
{
  umask(0);
  return fuse_main(argc, argv, &xmp_oper, NULL);
}
 

