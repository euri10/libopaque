#include <opaque.h>
#include <common.h>

int opaquejs_crypto_auth_hmacsha512_BYTES() {
  return crypto_auth_hmacsha512_BYTES;
}


int opaquejs_crypto_core_ristretto255_BYTES() {
  return crypto_core_ristretto255_BYTES;
}


int opaquejs_crypto_hash_sha512_BYTES() {
  return crypto_hash_sha512_BYTES;
}


int opaquejs_crypto_scalarmult_BYTES() {
  return crypto_scalarmult_BYTES;
}


int opaquejs_crypto_scalarmult_SCALARBYTES() {
  return crypto_scalarmult_SCALARBYTES;
}


int opaquejs_OPAQUE_USER_RECORD_LEN() {
  return OPAQUE_USER_RECORD_LEN;
}


int opaquejs_OPAQUE_REGISTER_PUBLIC_LEN() {
  return OPAQUE_REGISTER_PUBLIC_LEN;
}


int opaquejs_OPAQUE_REGISTER_SECRET_LEN() {
  return OPAQUE_REGISTER_SECRET_LEN;
}


int opaquejs_OPAQUE_SERVER_SESSION_LEN() {
  return OPAQUE_SERVER_SESSION_LEN;
}


int opaquejs_OPAQUE_REGISTER_USER_SEC_LEN() {
  return OPAQUE_REGISTER_USER_SEC_LEN;
}


int opaquejs_OPAQUE_USER_SESSION_PUBLIC_LEN() {
  return OPAQUE_USER_SESSION_PUBLIC_LEN;
}


int opaquejs_OPAQUE_USER_SESSION_SECRET_LEN() {
  return OPAQUE_USER_SESSION_SECRET_LEN;
}

int opaquejs_OPAQUE_SHARED_SECRETBYTES() {
  return OPAQUE_SHARED_SECRETBYTES;
}

int opaquejs_OPAQUE_REGISTRATION_RECORD_LEN() {
  return OPAQUE_REGISTRATION_RECORD_LEN;
}

int opaquejs_TOPRF_Share_BYTES() {
   return TOPRF_Share_BYTES;
}

int opaquejs_TOPRF_Part_BYTES() {
   return TOPRF_Part_BYTES;
}

int opaquejs_GenServerKeyPair(
  uint8_t pkS[crypto_scalarmult_BYTES],
  uint8_t skS[crypto_scalarmult_SCALARBYTES]) {

  randombytes(skS, crypto_scalarmult_SCALARBYTES);
  return crypto_scalarmult_ristretto255_base(pkS, skS);
}


int opaquejs_Register(
  const uint8_t *pwdU,
  const uint16_t pwdU_len,
  const uint8_t skS[crypto_scalarmult_SCALARBYTES],
  const uint8_t *ids_idU,
  const uint16_t ids_idU_len,
  const uint8_t *ids_idS,
  const uint16_t ids_idS_len,
  uint8_t rec[OPAQUE_USER_RECORD_LEN],
  uint8_t export_key[crypto_hash_sha512_BYTES]) {

  const Opaque_Ids ids = { ids_idU_len, (uint8_t *)ids_idU, ids_idS_len, (uint8_t *)ids_idS };
  return opaque_Register(pwdU, pwdU_len, skS, &ids, rec, export_key);
}


int opaquejs_CreateCredentialRequest(
  const uint8_t *pwdU,
  const uint16_t pwdU_len,
  uint8_t sec[OPAQUE_USER_SESSION_SECRET_LEN+pwdU_len],
  uint8_t pub[OPAQUE_USER_SESSION_PUBLIC_LEN]) {

  return opaque_CreateCredentialRequest(pwdU, pwdU_len, sec, pub);
}


int opaquejs_CreateCredentialResponse(
  const uint8_t pub[OPAQUE_USER_SESSION_PUBLIC_LEN],
  const uint8_t rec[OPAQUE_USER_RECORD_LEN],
  const uint8_t *ids_idU,
  const uint16_t ids_idU_len,
  const uint8_t *ids_idS,
  const uint16_t ids_idS_len,
  const uint8_t *ctx,
  const uint16_t ctx_len,
  uint8_t resp[OPAQUE_SERVER_SESSION_LEN],
  uint8_t sk[OPAQUE_SHARED_SECRETBYTES],
  uint8_t sec[crypto_auth_hmacsha512_BYTES]) {

  const Opaque_Ids ids = { ids_idU_len, (uint8_t *)ids_idU, ids_idS_len, (uint8_t *)ids_idS };
  return opaque_CreateCredentialResponse(pub, rec, &ids, ctx, ctx_len, resp, sk, sec);
}


int opaquejs_RecoverCredentials(
  const uint8_t resp[OPAQUE_SERVER_SESSION_LEN],
  const uint8_t sec[OPAQUE_USER_SESSION_SECRET_LEN /*+pwdU_len*/],
  const uint8_t *ctx,
  const uint16_t ctx_len,
  const uint8_t *ids_idU,
  const uint16_t ids_idU_len,
  const uint8_t *ids_idS,
  const uint16_t ids_idS_len,
  uint8_t sk[OPAQUE_SHARED_SECRETBYTES],
  uint8_t authU[crypto_auth_hmacsha512_BYTES],
  uint8_t export_key[crypto_hash_sha512_BYTES]) {

  const Opaque_Ids ids = { ids_idU_len, (uint8_t *)ids_idU, ids_idS_len, (uint8_t *)ids_idS };
  if (0 != opaque_RecoverCredentials(resp, sec, ctx, ctx_len, &ids, sk, authU, export_key))
    return 1;
  return 0;
}


int opaquejs_UserAuth(
  uint8_t sec[crypto_auth_hmacsha512_BYTES],
  const uint8_t authU[crypto_auth_hmacsha512_BYTES]) {

  return opaque_UserAuth(sec, authU);
}


int opaquejs_CreateRegistrationRequest(
  const uint8_t *pwdU,
  const uint16_t pwdU_len,
  uint8_t sec[OPAQUE_REGISTER_USER_SEC_LEN+pwdU_len],
  uint8_t M[crypto_core_ristretto255_BYTES]) {

  return opaque_CreateRegistrationRequest(pwdU, pwdU_len, sec, M);
}


int opaquejs_CreateRegistrationResponse(
  const uint8_t M[crypto_core_ristretto255_BYTES],
  const uint8_t skS[crypto_scalarmult_SCALARBYTES],
  uint8_t sec[OPAQUE_REGISTER_SECRET_LEN],
  uint8_t pub[OPAQUE_REGISTER_PUBLIC_LEN]) {

  return opaque_CreateRegistrationResponse(M, skS, sec, pub);
}


int opaquejs_FinalizeRequest(
  const uint8_t sec[OPAQUE_REGISTER_USER_SEC_LEN /*+pwdU_len*/],
  const uint8_t pub[OPAQUE_REGISTER_PUBLIC_LEN],
  const uint8_t *ids_idU,
  const uint16_t ids_idU_len,
  const uint8_t *ids_idS,
  const uint16_t ids_idS_len,
  uint8_t rec[OPAQUE_REGISTRATION_RECORD_LEN],
  uint8_t export_key[crypto_hash_sha512_BYTES]) {

  const Opaque_Ids ids = { ids_idU_len, (uint8_t *)ids_idU, ids_idS_len, (uint8_t *)ids_idS };
  return opaque_FinalizeRequest(sec, pub, &ids, rec, export_key);
}


void opaquejs_StoreUserRecord(
  const uint8_t sec[OPAQUE_REGISTER_SECRET_LEN],
  const uint8_t recU[OPAQUE_REGISTRATION_RECORD_LEN],
  uint8_t rec[OPAQUE_USER_RECORD_LEN]) {

  opaque_StoreUserRecord(sec, recU, rec);
}

int opaquejs_3hashtdh(
      const uint8_t k[TOPRF_Share_BYTES],
      const uint8_t z[TOPRF_Share_BYTES],
      const uint8_t alpha[crypto_core_ristretto255_BYTES],
      const uint8_t *ssid_S, const uint16_t ssid_S_len,
      uint8_t beta[TOPRF_Part_BYTES]) {
   return toprf_3hashtdh(k, z, alpha, ssid_S, ssid_S_len, beta);
}
