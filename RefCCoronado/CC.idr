module RefCCoronado.CC

import Core.Context
import Core.Context.Log
import Core.Options
import Core.Directory

import System

%default total

findCC : IO String
findCC
    = do Nothing <- getEnv "IDRIS2_CC"
           | Just cc => pure cc
         Nothing <- getEnv "CC"
           | Just cc => pure cc
         pure "cc"

public export
data TargetType = Shared | Static | Exec

export
Eq TargetType where
  Shared == Shared = True
  Static == Static = True
  Exec == Exec = True
  _ == _ = False

export
compileCObjectFile : {auto c : Ref Ctxt Defs}
                  -> {default Shared targetType : TargetType}
                  -> (sourceFile : String)
                  -> (objectFile : String)
                  -> Core (Maybe String)
compileCObjectFile {targetType=Shared} sourceFile objectFile =
  do cc <- coreLift findCC
     refcDir <- findDataFile "refc"
     cDir <- findDataFile "c"
     let runccobj = cc ++ " -Werror -c -fpic " ++ sourceFile ++
                       " -o " ++ objectFile ++
                       " -I" ++ refcDir ++
                       " -I" ++ cDir
     log "compiler.refc.cc" 10 runccobj
     0 <- coreLift $ system runccobj
       | _ => pure Nothing
     pure (Just objectFile)

compileCObjectFile {targetType=_} sourceFile objectFile =
  do cc <- coreLift findCC
     refcDir <- findDataFile "refc"
     cDir <- findDataFile "c"
     let runccobj = cc ++ " -Werror -c " ++ sourceFile ++
              " -o " ++ objectFile ++
              " -I" ++ refcDir ++
              " -I" ++ cDir
     log "compiler.refc.cc" 10 runccobj
     0 <- coreLift $ system runccobj
        | _ => pure Nothing
     pure (Just objectFile)




clibdirs : List String -> String
clibdirs ds = concat (map (\d => "-L" ++ d ++ " ") ds)


export
compileStep2 : {auto c : Ref Ctxt Defs}
            -> {default Shared targetType : TargetType}
            -> (objectFile : String)
            -> (outFile : String)
            -> Core (Maybe String)
compileStep2  {targetType=Shared} objectFile outFile =
  do cc <- coreLift findCC
     dirs <- getDirs
     refcDir <- findDataFile "refc"
     supportFile <- findLibraryFile "libidris2_support.a"

     let sharedFlag = "-shared "

     let runcc = cc ++ " -Werror " ++ sharedFlag ++ objectFile ++
                       " -o " ++ outFile ++ " " ++
                       supportFile ++ " " ++
                       "-lidris2_refc " ++
                       "-L" ++ refcDir ++ " " ++
                       clibdirs (lib_dirs dirs) ++
                       "-lgmp -lm"

     log "compiler.refc.cc" 10 runcc
     0 <- coreLift $ system runcc
       | _ => pure Nothing

     pure (Just outFile)
compileStep2  {targetType=Static} objectFile outFile =
  do cc <- coreLift findCC
     dirs <- getDirs
     refcDir <- findDataFile "refc"


     let runcc = "ar rcs " ++ outFile ++ " " ++ objectFile

     log "compiler.refc.cc" 10 runcc
     0 <- coreLift $ system runcc
       | _ => pure Nothing

     pure (Just outFile)
compileStep2  {targetType=Exec} objectFile outFile =
  do cc <- coreLift findCC
     dirs <- getDirs
     refcDir <- findDataFile "refc"
     supportFile <- findLibraryFile "libidris2_support.a"

     let runcc = cc ++ " -Werror " ++ objectFile ++
                      " -o " ++ outFile ++ " " ++
                      supportFile ++ " " ++
                      "-lidris2_refc " ++
                      "-L" ++ refcDir ++ " " ++
                      clibdirs (lib_dirs dirs) ++
                      "-lgmp -lm -O2"


     log "compiler.refc.cc" 10 runcc
     0 <- coreLift $ system runcc
      | _ => pure Nothing

     pure (Just outFile)
