##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCGames
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/Jas/Documents/_projectosCodeLite/PR3
ProjectPath            :=C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jas
Date                   :=21/12/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../lib/$(ProjectName).lib
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UOCGames.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/src_ranking.c$(ObjectSuffix) $(IntermediateDirectory)/src_team.c$(ObjectSuffix) $(IntermediateDirectory)/src_competition.c$(ObjectSuffix) $(IntermediateDirectory)/src_player.c$(ObjectSuffix) $(IntermediateDirectory)/src_match.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "C:\Users\Jas\Documents\_projectosCodeLite\PR3/.build-debug"
	@echo rebuilt > "C:\Users\Jas\Documents\_projectosCodeLite\PR3/.build-debug/UOCGames"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_ranking.c$(ObjectSuffix): src/ranking.c $(IntermediateDirectory)/src_ranking.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames/src/ranking.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ranking.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ranking.c$(DependSuffix): src/ranking.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ranking.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ranking.c$(DependSuffix) -MM src/ranking.c

$(IntermediateDirectory)/src_ranking.c$(PreprocessSuffix): src/ranking.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ranking.c$(PreprocessSuffix) src/ranking.c

$(IntermediateDirectory)/src_team.c$(ObjectSuffix): src/team.c $(IntermediateDirectory)/src_team.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames/src/team.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_team.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_team.c$(DependSuffix): src/team.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_team.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_team.c$(DependSuffix) -MM src/team.c

$(IntermediateDirectory)/src_team.c$(PreprocessSuffix): src/team.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_team.c$(PreprocessSuffix) src/team.c

$(IntermediateDirectory)/src_competition.c$(ObjectSuffix): src/competition.c $(IntermediateDirectory)/src_competition.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames/src/competition.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_competition.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_competition.c$(DependSuffix): src/competition.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_competition.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_competition.c$(DependSuffix) -MM src/competition.c

$(IntermediateDirectory)/src_competition.c$(PreprocessSuffix): src/competition.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_competition.c$(PreprocessSuffix) src/competition.c

$(IntermediateDirectory)/src_player.c$(ObjectSuffix): src/player.c $(IntermediateDirectory)/src_player.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames/src/player.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_player.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_player.c$(DependSuffix): src/player.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_player.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_player.c$(DependSuffix) -MM src/player.c

$(IntermediateDirectory)/src_player.c$(PreprocessSuffix): src/player.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_player.c$(PreprocessSuffix) src/player.c

$(IntermediateDirectory)/src_match.c$(ObjectSuffix): src/match.c $(IntermediateDirectory)/src_match.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Jas/Documents/_projectosCodeLite/PR3/UOCGames/src/match.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_match.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_match.c$(DependSuffix): src/match.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_match.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_match.c$(DependSuffix) -MM src/match.c

$(IntermediateDirectory)/src_match.c$(PreprocessSuffix): src/match.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_match.c$(PreprocessSuffix) src/match.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


