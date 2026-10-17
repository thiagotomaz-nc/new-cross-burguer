// 0 - CANCELADO, 1 - EM CONSTRUÇÃO, 2 - FECHADO, 3 - PRONTO
// int sttus = static_cast<int>(Status::Cancelado);


#pragma once //impede que o mesmo arquivo .h seja incluído mais de uma vez durante a compilação.

enum class StatusOrder{
    CANCELADO,
    EM_CONSTRUCAO,
    FECHADO,
    PREPARO,
    COZINHA,
    PRONTO,
    FINALIZADO, 
};