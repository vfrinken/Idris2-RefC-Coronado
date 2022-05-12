module Main

import Core.Context
import Compiler.Common
import Idris.Driver

import RefCCoronado.RefC
import RefCCoronado.CC


codegenRefCShared : Codegen
codegenRefCShared = MkCG (compileExprToLib ANF Shared) executeExpr Nothing Nothing


codegenRefCCoronadoStatic : Codegen
codegenRefCCoronadoStatic = MkCG (compileExprToLib ANF Static) executeExpr Nothing Nothing


codegenRefCCoronado : Codegen
codegenRefCCoronado = MkCG (compileExprToLib ANF Exec) executeExpr Nothing Nothing


main : IO ()
main = mainWithCodegens [
    ("refc-coronado", codegenRefCCoronado),
    ("refc-coronado-shared", codegenRefCShared),
    ("refc-coronado-static", codegenRefCCoronadoStatic)]
