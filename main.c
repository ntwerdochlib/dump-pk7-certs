#include <stdio.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <openssl/bio.h>
#include <openssl/pem.h>

int main(int argc, char **argv)
{
    PKCS7 *p7 = NULL;
    BIO *in = BIO_new(BIO_s_file());
    BIO *out = BIO_new(BIO_s_file());
    int der = 0; /* Input from DER or PEM ? */
    int text = 0; /* Dump text or output PEM ? */
    STACK_OF(X509) *certs = NULL;
    int i;

    CRYPTO_malloc_init();                                               \
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    BIO_set_fp(out, stdout, BIO_NOCLOSE);
    BIO_read_filename(in, argv[1]);
    p7 = der ?
        d2i_PKCS7_bio(in, NULL) :
        PEM_read_bio_PKCS7(in, NULL, NULL, NULL);

    i = OBJ_obj2nid(p7->type);
    if(i == NID_pkcs7_signed) {
        certs = p7->d.sign->cert;
    } else if(i == NID_pkcs7_signedAndEnveloped) {
        certs = p7->d.signed_and_enveloped->cert;
    }

    for (i = 0; certs && i < sk_X509_num(certs); i++) {
        X509 *x = sk_X509_value(certs,i);
        if(text) {
            X509_print(out, x);
        } else {
            PEM_write_bio_X509(out,x);
        }
    }
}
