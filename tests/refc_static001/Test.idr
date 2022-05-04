module Main


import Data.IORef

%export "RefC:addTwoNumbers"
addTwoNumbers : Nat -> Nat -> Nat
addTwoNumbers a b = a + b


%export "RefC:execFct"
execFunction : Nat -> AnyPtr -> IO ()
execFunction _ _ = do
    putStrLn $ "execFunction test"


data ExportedFunction : Type where
    MkExportedFunction : {t:Type} -> (fct:t) -> ExportedFunction


main : IO ()
main = do
    let a = [ MkExportedFunction execFunction
            , MkExportedFunction addTwoNumbers]
    putStrLn $ show $ length a
