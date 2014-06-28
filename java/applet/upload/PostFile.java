import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpVersion;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.ContentBody;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.CoreProtocolPNames;
import org.apache.http.util.EntityUtils;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.content.StringBody;
import java.nio.charset.Charset;
import java.util.Objects;

public class PostFile {
  public static void main(String TargetUrl, String SourceFile, 
		                  String formFieldName) throws Exception {
    HttpClient httpclient = new DefaultHttpClient();
    httpclient.getParams().setParameter(CoreProtocolPNames.PROTOCOL_VERSION, HttpVersion.HTTP_1_1);

    HttpPost httppost = new HttpPost(TargetUrl /*"http://localhost/post.php" */);
    File file = new File(SourceFile /*"/home/wus/.profile"*/);
    
    MultipartEntity mpEntity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
    upload.mimeType = Files.probeContentType(Paths.get(SourceFile));
    ContentBody cbFile = new FileBody(file, upload.mimeType); // TODO: find appropriate content-type
    mpEntity.addPart(formFieldName, cbFile);
    
    mpEntity.addPart("content-type", new StringBody(upload.mimeType, "text/plain",
	         Charset.forName( "UTF-8" )));
    
    File f = new File(SourceFile);
    String l = Objects.toString(f.length(), null);
    mpEntity.addPart("size", new StringBody(l, "text/plain",
	                 Charset.forName( "UTF-8" )));

    httppost.setEntity(mpEntity);
    System.out.println("executing request " + httppost.getRequestLine());
    HttpResponse response = httpclient.execute(httppost);
    HttpEntity resEntity = response.getEntity();
    

    System.out.println(response.getStatusLine());
    if (resEntity != null) {
      System.out.println(response.getStatusLine().getStatusCode());
      System.out.println(EntityUtils.toString(resEntity));
      upload.statusCode = response.getStatusLine().getStatusCode();
    }
    if (resEntity != null) {
      resEntity.consumeContent();
    }

    httpclient.getConnectionManager().shutdown();
  }
}
