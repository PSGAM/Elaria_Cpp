// This class is based on the one in the book "Programming AI by Example" by Mat Buckland.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MessageInfo.generated.h"


USTRUCT(BlueprintType)
struct ELARIA_API FMessageInfo
{
	GENERATED_BODY()

		// The entity that sent this telegram
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Sender;

	// The entity that is to receive this telegram
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Receiver;

	// The message itself. These are all enumerated in the file
	// "MessageTypes.h"
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Msg;

	// Messages can ce dispatched inmidietly or delayed for a specific
	//   amount of time. If a delay is necessary, this field is stamped
	//   with the time the message should be dispatched.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DispatchTime;

	// Any additional information that might acompany the message.
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// UObject* ExtraInfo;
};

